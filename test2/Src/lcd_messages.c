/*
 * lcd_messages.c
 *
 *  Created on: 09. dec. 2019.
 *      Author: Administrator
 */
#include "lcd_messages.h"
#include "i2c-lcd.h"
#include "data_separate.h"

void lcd_configuration_mode(){
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd (0x88 - strlen("Configuration")/2);  // goto 1,1
	lcd_send_string("Configuration");
	lcd_send_cmd (0xc8 - strlen("mode")/2);
	lcd_send_string("mode");
	HAL_Delay (2000);
}

void lcd_successfully_added(){
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd(0x88 - strlen("successfully")/2);
	lcd_send_string("Successfully");
	lcd_send_cmd(0xc8 - strlen("added")/2);
	lcd_send_string("added");
	HAL_Delay(2000);
	lcd_configuration_mode();
}


void lcd_max_limit(){
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd(0x80);
	lcd_send_string("MAX LIMIT");
	lcd_send_cmd(0xc0);
	lcd_send_string("REACHED");
}

void lcd_name_surname(uint8_t* name, uint8_t* surname){
	int first, second = 0;
	first = center_word(name);
	second = center_word(surname);
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd(0x88 - first);
	lcd_send_string(name);
	lcd_send_cmd(0xc8 - second);
	lcd_send_string(surname);
	HAL_Delay(1000);

}

void lcd_eeprom_cleared(){
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd(0x80);
	lcd_send_string("EEPROM");
	lcd_send_cmd(0xc0);
	lcd_send_string("Cleared");
	HAL_Delay(2000);
	lcd_configuration_mode();
}

void lcd_no_entries(){
	lcd_send_cmd(0x01);
	HAL_Delay(10);
	lcd_send_cmd(0x88 - strlen("no")/2);
	lcd_send_string("No");
	lcd_send_cmd(0xc8 - strlen("entries")/2);
	lcd_send_string("Entries");
	HAL_Delay(2000);
}

void lcd_clear(){
	lcd_send_cmd(0x01);
}

