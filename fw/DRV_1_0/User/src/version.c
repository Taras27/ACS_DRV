/*
 * version.c
 *
 *  Created on: Dec 17, 2023
 *      Author: Taras Horyn
 */

#include "version.h"
#include "stm32f0xx_hal.h"


#define HW_REV_H	1
#define HW_REV_L	0

#define SW_REV_H	1
#define SW_REV_L	0


#define DATE_YEAR	23
#define DATE_MONTH	9
#define DATE_DAY	11

#define TIME_HOUR	14
#define TIME_MIN	55
#define TIME_SEC	00


void VERSION_Init(VERSION_Data *data)
{
	data->REV_HW_H 		= HW_REV_H;
	data->REV_HW_L 		= HW_REV_L;

	data->REV_SW_H 		= SW_REV_H;
	data->REV_SW_L 		= SW_REV_L;

	data->DATE_Year 	= DATE_YEAR;
	data->DATE_Mounth 	= DATE_MONTH;
	data->DATE_Day 		= DATE_DAY;

	data->TIME_Hour 	= TIME_HOUR;
	data->TIME_Min 		= TIME_MIN;
	data->TIME_Sec 		= TIME_SEC;

	//MCU ID
	data->DEV_Id 		= HAL_GetDEVID();

	data->SN_0 			= HAL_GetUIDw0();
	data->SN_1 			= HAL_GetUIDw1();
	data->SN_2 			= HAL_GetUIDw2();
}


