/*
 * hc06.c
 *
 *  Created on: 11. dec. 2019.
 *      Author: Administrator
 */

#include "stm32f1xx_hal.h"
#include "data_separate.h"
#include "eeprom24xx.h"
#include "mode.h"

/*Store data received from BT
 * int name_ad: First free address for storing name and surname
 * int number_ad: First free address for storing number
 * int entries: Number of entries
 * uint8_t* data: Pointer to data received through BT
 * */
void BT_store(int name_ad, int number_ad,int entries, uint8_t* data){
	Struct result1;
	int entries_number = entries; //number of entries
	uint8_t del[BT_DATA]= "";
	uint8_t entry_data[] = "";
	result1 = NS_number_separation(data); //sepparate string received from BT
	EEPROM24XX_Save(name_ad, result1.NS_pointer, DATA_LENGTH); //Store name_surname on EEPROM
	EEPROM24XX_Save(number_ad, result1.number_pointer, DATA_LENGTH); //Store number on EEPROM
	entries_number++; //Increase number of entries
	itoa(entries_number, entry_data, 10); //convert number of entries from int to string
	EEPROM24XX_Save(NO_ENTRIESADD, entry_data, DATA_LENGTH); //store number of entries
	successfully_added_lcd(); //message display
	memcpy(data, del, strlen(data)); //clear data buffer

}

//Delete all data from EEPROM
void clear_eeprom(){
	uint8_t del=0xff;
	for(int i = 0; i <= NO_ENTRIESADD; i++){
		EEPROM24XX_Save(i, del, DATA_LENGTH);
	}
}

