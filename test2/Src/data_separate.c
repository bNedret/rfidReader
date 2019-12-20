/*
 * data_separate.c
 *
 *  Created on: 10. dec. 2019.
 *      Author: Administrator
 */
#include "data_separate.h"
#include "stm32f1xx_hal.h"
#include "mode.h"

/*Initialize configuration mode
 * Load number of entries
 * Display message on LCD
 * */
uint32_t configuration_mode_init(){
	uint32_t entries_number; //number of entries
	uint8_t ent_number[DATA_LENGTH];
	configuration_mode_lcd(); //display message
	EEPROM24XX_Load(NO_ENTRIESADD, ent_number, DATA_LENGTH); //load number of entries from EEPROM
	entries_number = atoi(ent_number); //convert string to int
	return entries_number;
}

/*Initialization when working mode is selected.
 *Loads name and surname from address 0 and displays it on LCD.*/
uint32_t working_mode_init(){
	Struct result;
	uint32_t entries_number;
	uint8_t ent_number[DATA_LENGTH];
	uint8_t data[DATA_LENGTH];
	EEPROM24XX_Load(NS_STARTADD, data, DATA_LENGTH);
	if (strcmp(data, "") == 0){
		no_entries();
	}
	else{
		result = name_surname_separation(data);
		name_surname_lcd(result.name_pointer, result.surname_pointer);
	}

	EEPROM24XX_Load(NO_ENTRIESADD, ent_number, DATA_LENGTH);
	entries_number = atoi(ent_number);
	return entries_number;
}

int center_word(uint8_t* word1){
	int first_mid = 0;
	return first_mid = strlen(word1)/2;
}

/*Separates string received through bluetooth
 * String format: "name_surname number"
 * Separation format: "name_surname", "number"*/
Struct NS_number_separation(uint8_t* data){
	Struct result;
	result.NS_pointer = strtok(data, " ");
	result.number_pointer = strtok(NULL, " ");
	return result;
}

/*Separates string received through EEPROM
 * String format: "name_surname"
 * Separation format: "name", "surname"*/
Struct name_surname_separation(uint8_t* data){
	Struct result;
	result.name_pointer = strtok(data, "_");
	result.surname_pointer = strtok(NULL, "_");
	return result;
}
