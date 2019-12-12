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

/*For configuration mode:
 * Receiving data format: 'name_surname number'
 * Separate it by " " on 'name_surname' and 'number'
 * For working mode:
 * Two strings name and number
 * Separate 'name_surname' by "_"*/


int entries_number;

//Bluetooth module active, and receiving data
void configuration_mode(){
	Struct result;
	uint8_t del[BT_DATA]= "";
	int radd_name, radd_number = 0;
	uint8_t receive_data[BT_DATA];
	radd_name = configuration_mode_init();
	radd_name = entries_number * DATA_LENGTH; //address of latest name
	radd_number = NUMBER_STARTADD + radd_name; //address of latest number

	//still configuration mode
	while (HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_SET){
		if(radd_name <= NS_ENDADD && HAL_UART_GetState() == HAL_UART_STATE_READY){
			HAL_UART_Receive(&huart3, receive_data, 1000); // receive data via bluetooth
			//check if data is not empty
			if(strcmp(receive_data, "") != 0){
				result = NS_number_separation(receive_data);
				EEPROM24XX_Save(radd_name, result.NS_pointer, DATA_LENGTH); //Store name_surname on EEPROM
				EEPROM24XX_Save(radd_number, result.number_pointer, DATA_LENGTH); //Store number on EEPROM
				radd_name = radd_name + DATA_LENGTH; //Increase NS address
				radd_number = radd_number + DATA_LENGTH; //Increase number address
				entries_number++; //Increase number of entries
				EEPROM24XX_Save(NO_ENTRIESADD, entries_number, 2);
				successfully_added_lcd();
				memcpy(receive_data, del, strlen(receive_data));
			}

		}
		else{
			max_limit_lcd();
		}

	}


}

void working_mode(){
	int radd = 0;
	working_mode_init();

	while(HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_RESET){

		//Increment in Db
		if(HAL_GPIO_ReadPin(GPIOA, BUTTON_UP_PIN_Pin) == GPIO_PIN_RESET){
			HAL_GPIO_TogglePin(EXLED_GPIO_Port, EXLED_Pin);
			radd = button_up(radd);
		}
		//Decrement in Db
		else if(HAL_GPIO_ReadPin(GPIOA, BUTTON_DOWN_PIN_Pin) == GPIO_PIN_RESET){
			HAL_GPIO_TogglePin(EXLED_GPIO_Port, EXLED_Pin);
			radd = button_down(radd);
		}
		else if(HAL_GPIO_ReadPin(GPIOA, BUTTON_CALL_PIN_Pin)== GPIO_PIN_RESET){

		}

	}
}




