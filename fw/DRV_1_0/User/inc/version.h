/*
 * version.h
 *
 *  Created on: Dec 17, 2023
 *      Author: Taras Horyn
 */

#ifndef INC_VERSION_H_
#define INC_VERSION_H_

#include <stdint.h>


typedef struct
{
	volatile uint8_t REV_HW_H;
	volatile uint8_t REV_HW_L;

	volatile uint8_t REV_SW_H;
	volatile uint8_t REV_SW_L;

	volatile uint8_t DATE_Year;
	volatile uint8_t DATE_Mounth;
	volatile uint8_t DATE_Day;

	volatile uint8_t TIME_Hour;
	volatile uint8_t TIME_Min;
	volatile uint8_t TIME_Sec;

	volatile uint32_t DEV_Id;

	volatile uint32_t SN_0;
	volatile uint32_t SN_1;
	volatile uint32_t SN_2;
}VERSION_Data;

void VERSION_Init(VERSION_Data *data);

#endif /* INC_VERSION_H_ */
