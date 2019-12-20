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


//Bluetooth module active, and receiving data, storing it on EEPROM
void configuration_mode(){
	int radd_name, radd_number, entries_number = 0; //free address of Name_Surname, number and number of entries
	uint8_t receive_data[BT_DATA] = ""; //receiving data from HC06
	uint8_t del[BT_DATA]= ""; //used for clearing receive_data

	entries_number = configuration_mode_init(); //initialize configuration mode, and load number of entries
	radd_name = entries_number * DATA_LENGTH; //address of latest name
	radd_number = NUMBER_STARTADD + radd_name; //address of latest number

	//still configuration mode
	while (HAL_GPIO_ReadPin(MODE_GPIO_Port, MODE_Pin) == GPIO_PIN_SET){
		if(radd_name <= NS_ENDADD && HAL_UART_GetState(&huart3) == HAL_UART_STATE_READY){
			HAL_UART_Receive(&huart3, receive_data, BT_DATA, 5000); // receive data via bluetooth
			//check if data is not empty
			if(strcmp(receive_data, "") != 0){ //check if received data is not empty
				BT_store(radd_name, radd_number, entries_number, receive_data); //store data received through BT
				radd_name = radd_name + DATA_LENGTH; //increase store address for name and surname
				radd_number = radd_number + DATA_LENGTH; //increase store address for number
				entries_number++;
				memcpy(receive_data, del, strlen(receive_data)); //clear receive_data variable
			}
			else if (strcmp(receive_data, "1234") == 0){
				clear_eeprom();
			}

		}
		else{
			max_limit_lcd();
		}

	}


}

//Working mode
void working_mode(){
	int radd = 0;
	int entries_number;
	entries_number = working_mode_init();

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
			clear_eeprom();
			eeprom_cleared();
		}

	}
}




