/*
 * mode.h
 *
 *  Created on: 18. nov. 2019.
 *      Author: Administrator
 */

#ifndef MODE_H_
#define MODE_H_

#define NS_STARTADD 0 //Name and surname starting address
#define NS_ENDADD 160 //Name and surname last address
#define NUMBER_STARTADD 176 //Phone number starting address
#define NUMBER_ENDADD 336 //Phone number last address
#define DATA_LENGTH 16 //Data length when writing to eeprom
#define NO_ENTRIESADD 368 //Number of entries address
#define BT_DATA 32 //BT recive data length

void configuration_mode();
void working_mode();

#endif /* MODE_H_ */
