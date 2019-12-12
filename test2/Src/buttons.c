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
uint8_t data[data_length];

int button_up(int address){

	if(address > NS_endadd){
		address = 0;
	}
	EEPROM24XX_Load(address, data, data_length);
	result = name_surname_separation(data);
	name_surname_lcd(result.name_pointer, result.surname_pointer);
	return address + data_length;
}

int button_down(int address){
	if(address < NS_startadd){
		address = NS_endadd;
	}
	EEPROM24XX_Load(address, data, data_length);
	result = name_surname_separation(data);
	name_surname_lcd(result.name_pointer, result.surname_pointer);
	return address - data_length;
}

void button_call(){

}
