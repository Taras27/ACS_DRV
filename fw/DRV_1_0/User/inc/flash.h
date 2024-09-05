/*
 * flash.h
 *
 *  Created on: Dec 17, 2023
 *      Author: Taras Horyn
 */

#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include <stdint.h>

typedef struct
{
	volatile uint32_t WriteCount;

	volatile uint32_t BaudRate;
	volatile uint32_t WordLength;
	volatile uint32_t StopBits;
	volatile uint32_t Parity;
	volatile uint32_t DevAddr;

	volatile uint32_t Key;
}FLASH_Data;


uint8_t FLASH_Write (FLASH_Data *data);
uint8_t FLASH_Read (FLASH_Data *data);
uint8_t FLASH_Process(FLASH_Data *data, FLASH_Data *default_setting);
void FLASH_DefaultSetInit(FLASH_Data *default_setting);


#endif /* INC_FLASH_H_ */
