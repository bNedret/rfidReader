/*
 * mode.c
 *
 *  Created on: 18. nov. 2019.
 *      Author: Administrator
 */
#include "stm32f1xx_hal.h"
#include "mode.h"
#include "eeprom24xx.h"
#include "lcd_messages.h"
#include "data_separate.h"
#include "buttons.h"
#include "hc06.h"
#include "usart.h"

/* Number of entries indicate how many pairs of NS and number are stored
 * For configuration mode:
 * Receiving data format: 'name_surname number'
 * Separate it by " " on 'name_surname' and 'number'
 * For working mode:
 * Two strings name and number
 * Separate 'name_surname' by "_"*/


void configuration_mode(){
	int add_of_name, add_of_number, number_of_entries = 0;
	uint8_t receive_data_BT[BT_DATA] = "";
	uint8_t clear_buffer_BT[BT_DATA]= "";

	number_of_entries = init_configuration_mode(); //initialize configuration mode, and load number of entries
	add_of_name = number_of_entries * DATA_LENGTH; //address of latest name
	add_of_number = NUMBER_STARTADD + add_of_name; //address of latest number

	while (HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_SET){
		if(add_of_name <= NS_ENDADD && HAL_UART_GetState(&huart3) == HAL_UART_STATE_READY){
			HAL_UART_Receive(&huart3, receive_data_BT, BT_DATA, 5000);

			if(strcmp(receive_data_BT, "") != 0){
				BT_store(add_of_name, add_of_number, number_of_entries, receive_data_BT);
				add_of_name = add_of_name + DATA_LENGTH;
				add_of_number = add_of_number + DATA_LENGTH;
				number_of_entries++;
				memcpy(receive_data_BT, clear_buffer_BT, strlen(receive_data_BT));
			}
			else if (strcmp(receive_data_BT, "1234") == 0){
				clear_eeprom();
			}

		}
		else{
			lcd_max_limit();
		}

	}


}

void working_mode(){
	int radd = 0;
	int entries_number;
	entries_number = init_working_mode();

	while(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET){

		//Increment in Db
		if(HAL_GPIO_ReadPin(GPIOA, BUTTON_UP_PIN_Pin) == GPIO_PIN_RESET){
			//HAL_GPIO_TogglePin(EXLED_GPIO_Port, EXLED_Pin);
			radd = button_up(radd, entries_number);
		}
		//Decrement in Db
		else if(HAL_GPIO_ReadPin(GPIOA, BUTTON_DOWN_PIN_Pin) == GPIO_PIN_RESET){
			//HAL_GPIO_TogglePin(EXLED_GPIO_Port, EXLED_Pin);
			radd = button_down(radd, entries_number);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, BUTTON_CALL_PIN_Pin)== GPIO_PIN_RESET){
			button_call(radd);
		}

	}
}
