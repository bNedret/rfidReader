/*
 * lcd_messages.c
 *
 *  Created on: 09. dec. 2019.
 *      Author: Administrator
 */
#include "lcd_messages.h"
#include "i2c-lcd.h"

//Print on LCD after configuration mode is enterd
void configuration_mode_lcd(){
	lcd_send_cmd(0x01);
	lcd_send_cmd(0x80);
	lcd_send_string("Configuration");
	lcd_send_cmd(0xc0);
	lcd_send_string("mode");

}
//Print on LCD after entry from bluetooth is added
void successfully_added_lcd(){
	lcd_send_cmd(0x01);
	lcd_send_cmd(0x80);
	lcd_send_string("Successfully");
	lcd_send_cmd(0xc0);
	lcd_send_string("added");
	HAL_Delay(1000);
	configuration_mode();
}

void max_limit_lcd(){
	lcd_send_cmd(0x01);
	lcd_send_cmd(0x80);
	lcd_send_string("MAX LIMIT");
	lcd_send_cmd(0xc0);
	lcd_send_string("REACHED");
}
//Print on LCD name and surname loaded from EEPROM
void name_surname_lcd(uint8_t name, uint8_t surname){
	lcd_send_cmd(0x01);
	lcd_send_cmd(0x80);
	lcd_send_string(name);
	lcd_send_cmd(0xc0);
	lcd_send_string(surname);
	HAL_Delay(1000);

}


