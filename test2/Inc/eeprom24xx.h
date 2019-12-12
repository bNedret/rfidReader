/*
 * eeprom24xx.h
 *
 *  Created on: 13. nov. 2019.
 *      Author: Administrator
 */

#ifndef EEPROM24XX_H_
#define EEPROM24XX_H_

#include <stdbool.h>
#include "EEPROM24xxConfig.h"

bool		EEPROM24XX_IsConnected(void);
bool		EEPROM24XX_Save(uint16_t Address,void *data,size_t size_of_data);
bool		EEPROM24XX_Load(uint16_t Address,void *data,size_t size_of_data);


#endif /* EEPROM24XX_H_ */
