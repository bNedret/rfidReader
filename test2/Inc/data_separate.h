/*
 * data_separate.h
 *
 *  Created on: 10. dec. 2019.
 *      Author: Administrator
 */

#ifndef DATA_SEPARATE_H_
#define DATA_SEPARATE_H_

struct string_separate{
	uint8_t *NS_pointer; //Name and Surname Pointer for BT (configuration mode)
	uint8_t *number_pointer; //Number pointer for BT (configuration mode)
	uint8_t *name_pointer; //Name pointer (working mode)
	uint8_t *surname_pointer; //Surname pointer (working mode)
};
typedef struct string_separate Struct;

int configuration_mode_init();
void working_mode_init();
Struct NS_number_separation(uint8_t data);
Struct name_surname_separation(uint8_t data);

#endif /* DATA_SEPARATE_H_ */
