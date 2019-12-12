/*
 * data_separate.c
 *
 *  Created on: 10. dec. 2019.
 *      Author: Administrator
 */
#include "data_separate.h"
#include "stm32f1xx_hal.h"
#include "mode.h"

int configuration_mode_init(){
	int entries_number;
	configuration_mode_lcd();
	EEPROM24XX_Load(NO_ENTRIESADD, entries_number, 2);
	return entries_number;
}

/*Initialization when working mode is selected.
 *Loads name and surname from address 0 and displays it on LCD.*/
void working_mode_init(){
	Struct result;
	uint8_t data[DATA_LENGTH];
	EEPROM24XX_Load(NS_STARTADD, data, DATA_LENGTH);
	result = name_surname_separation(data);
	name_surname_lcd(result.name_pointer, result.surname_pointer);
}
/*Separates string coming from bluetooth
 * String format: "name_surname number"
 * Separation format: "name_surname", "number"*/
Struct NS_number_separation(uint8_t data){
	Struct result;
	result.NS_pointer = strtok(data, " ");
	result.number_pointer = strtok(NULL, " ");
	return result;
}

/*Separates string coming from EEPROM
 * String format: "name_surname"
 * Separation format: "name", "surname"*/
Struct name_surname_separation(uint8_t data){
	Struct result;
	result.name_pointer = strtok(data, "_");
	result.surname_pointer = strtok(data, "_");
	return result;
}
