/*
 * hc06.c
 *
 *  Created on: 11. dec. 2019.
 *      Author: Administrator
 */
#include "hc06.h"
#include "mode.h"
#include "usart.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"

void BT_receive(add){
	Struct result;
	uint8_t del[BT_DATA] = "";
	uint8_t receive_data_buffer[BT_DATA];
	int name_add, number_add;
	name_add = add * DATA_LENGTH;
	number_add = NUMBER_STARTADD + name_add;
	if (add <= NS_ENDADD && HAL_UART_GetState() == HAL_UART_STATE_READY){
		HAL_UART_Receive(&huart3, receive_data_buffer, BT_DATA, 1000);

		if(strcmp(receive_data_buffer, "") != 0){
			result = NS_number_separation(receive_data_buffer);
			EEPROM24XX_Load(add, result.NS_pointer, DATA_LENGTH);
			EEPROM24XX_Load(add, result.number_pointer, DATA_LENGTH);
			name_add = name_add + DATA_LENGTH;
			number_add = number_add + DATA_LENGTH;
			entries_number++;
			EEPROM24XX_Save(NO_ENTRIESADD, entries_number, 2);
			successfully_added_lcd();
			memcpy(receive_data_buffer, del, BT_DATA);
		}
	}

}

