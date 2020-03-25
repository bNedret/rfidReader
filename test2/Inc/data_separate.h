/*
 * data_separate.h
 *
 *  Created on: 10. dec. 2019.
 *      Author: Administrator
 */

#ifndef DATA_SEPARATE_H_
#define DATA_SEPARATE_H_

#include "main.h"
#include "stm32f1xx_hal.h"

struct string_separate{
	uint8_t *NS_pointer; //Name and Surname Pointer for BT (configuration mode)
	uint8_t *number_pointer; //Number pointer for BT (configuration mode)
	uint8_t *name_pointer; //Name pointer (working mode)
	uint8_t *surname_pointer; //Surname pointer (working mode)
};
typedef struct string_separate Struct;

uint32_t init_configuration_mode();
uint32_t init_working_mode();
int center_word(uint8_t* word1);
Struct separation_NS_number(uint8_t* data);
Struct separation_name_surname(uint8_t* data);

#endif /* DATA_SEPARATE_H_ */
