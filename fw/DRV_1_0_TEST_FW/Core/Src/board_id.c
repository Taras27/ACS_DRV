/*
 * board_id.c
 *
 *  Created on: May 30, 2025
 *      Author: Taras Horyn
 */
 
#include "board_id.h"
#include "board_id_cfg.h"
#include "stm32g0xx_hal.h"
#include <stdint.h>

#define BOARD_ID_HIGH		ID_HIGH
#define ID_PIN_COUNT		PIN_COUNT

HW_ID_PIN_S id_pin[3] = {
		{GPIOA, GPIO_PIN_0},
		{GPIOA, GPIO_PIN_1},
		{GPIOB, GPIO_PIN_2}};

uint8_t BOARD_ID_Get(void)
{
	uint8_t id = 0xFF;
	uint8_t temp_id = 0;
	
	for(uint8_t i = 0; i < ID_PIN_COUNT; i++)
	{
		temp_id |= (HAL_GPIO_ReadPin(id_pin[i].port, id_pin[i].pin) << i);
	}
	
	id = temp_id | BOARD_ID_HIGH;
	
	return id;
}
