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
void successfully_added_lcd();
void configuration_mode_lcd();
void max_limit_lcd();
void eeprom_cleared();
void no_entries();
void name_surname_lcd(uint8_t* name, uint8_t* surname);

#endif /* LCD_MESSAGES_H_ */
