/*
 * lcd_messages.h
 *
 *  Created on: 09. dec. 2019.
 *      Author: Administrator
 */

#ifndef LCD_MESSAGES_H_
#define LCD_MESSAGES_H_
#include "main.h"
#include "stm32f1xx_hal.h"
void lcd_successfully_added();
void lcd_configuration_mode();
void lcd_max_limit();
void lcd_eeprom_cleared();
void lcd_no_entries();
void lcd_name_surname(uint8_t* name, uint8_t* surname);
void lcd_clear();

#endif /* LCD_MESSAGES_H_ */
