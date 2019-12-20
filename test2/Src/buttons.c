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
	int name_surname_eadd = 0; //name_surname last data stored address
	name_surname_eadd = entries_number * DATA_LENGTH - 16;
	if(address > name_surname_eadd){ //check if address exceed set number of entries
		address = NS_STARTADD; //go to starting address
	}
	EEPROM24XX_Load(address, data, DATA_LENGTH);
	result = name_surname_separation(data);
	name_surname_lcd(result.name_pointer, result.surname_pointer);
	return address + DATA_LENGTH;
}

/* Load previous entry from EEPROM
 * int address: address that should be loaded from
 * int entries_number: number of entries
 * */
int button_down(int address, int entries_number){
	int name_surname_eadd = 0; //name_surname last data stored address
	name_surname_eadd = entries_number * DATA_LENGTH -16;
	if(address < NS_STARTADD){ //check if address subceed starting address
		address = name_surname_eadd; //go to last address
	}
	EEPROM24XX_Load(address, data, DATA_LENGTH);
	result = name_surname_separation(data);
	name_surname_lcd(result.name_pointer, result.surname_pointer);
	return address - DATA_LENGTH;
}

void button_call(){

}
