/*
 * buttons.c
 *
 *  Created on: 02. apr. 2019.
 *      Author: Administrator
 */
#include "buttons.h"
#include "stm32f1xx_hal.h"
#include "data_separate.h"
#include "lcd_messages.h"
#include "eeprom24xx.h"
#include "mode.h"

Struct result;
uint8_t data[DATA_LENGTH];

/* Load next entry from EEPROM
 * int address: address that should be loaded from
 * int entries_number: number of entries
 * */
int button_up(int address, int entries_number){
	address = address + 16;
	int name_surname_eadd = entries_number * DATA_LENGTH - 16;
	if(address > name_surname_eadd){
		address = NS_STARTADD;
	}
	EEPROM24XX_Load(address, data, DATA_LENGTH);
	result = separation_name_surname(data);
	lcd_name_surname(result.name_pointer, result.surname_pointer);
	return address;
}

/* Load previous entry from EEPROM
 * int address: address that should be loaded from
 * int entries_number: number of entries
 * */
int button_down(int address, int entries_number){
	address = address - 16;
	int name_surname_eadd = entries_number * DATA_LENGTH -16;
	if(address < NS_STARTADD){
		address = name_surname_eadd;
	}
	EEPROM24XX_Load(address, data, DATA_LENGTH);
	result = separation_name_surname(data);
	lcd_name_surname(result.name_pointer, result.surname_pointer);
	return address;
}

void button_call(int address){
	EEPROM24XX_Load(NUMBER_STARTADD+address, data, DATA_LENGTH);
	lcd_name_surname("Number is:", data);
}
