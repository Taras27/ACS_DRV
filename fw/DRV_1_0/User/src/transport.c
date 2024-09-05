/*
 * transport.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Taras Horyn
 */

#include "stm32g0xx_hal.h"
#include "usart.h"
#include "transport.h"
#include <stdbool.h>
#include <string.h>

static uint8_t data_to_read_len = 0;
static uint8_t data_buffer[BUFFER_SIZE] = { 0 };
static uint8_t buffer_rx[BUFFER_SIZE] = { 0 };

void TRANSPORT_Init(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_UARTEx_ReceiveToIdle_IT(&huart2, buffer_rx, BUFFER_SIZE);
}

void TRANSPORT_ReadData(uint8_t *data, uint8_t len)
{
	memcpy(data, data_buffer, len);
	memset(data_buffer, 0x00, len);
	data_to_read_len = 0;
}

void TRANSPORT_WriteData(uint8_t *data, uint8_t len)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_UART_Transmit_IT(&huart2, data, len);
}

uint8_t TRANSPORT_IsDataAvailable(void)
{
	return data_to_read_len;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{
		HAL_UART_RxEventTypeTypeDef temp_rx_even = HAL_UARTEx_GetRxEventType(huart);

		if(temp_rx_even == HAL_UART_RXEVENT_IDLE)
		{
			data_to_read_len = Size;
			memcpy(data_buffer, buffer_rx, Size);
			memset(buffer_rx, 0x00, Size);
			HAL_UARTEx_ReceiveToIdle_IT(huart, buffer_rx, BUFFER_SIZE);
		}

	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART2)
	{
		uint32_t uart_temp_error = HAL_UART_GetError(huart);

		switch(uart_temp_error)
		{
			case HAL_UART_ERROR_PE: __HAL_UART_CLEAR_PEFLAG(huart); break;
			case HAL_UART_ERROR_NE: __HAL_UART_CLEAR_NEFLAG(huart); break;
			case HAL_UART_ERROR_FE: __HAL_UART_CLEAR_FEFLAG(huart); break;
			case HAL_UART_ERROR_ORE: __HAL_UART_CLEAR_OREFLAG(huart); break;
		}
		huart->ErrorCode = HAL_UART_ERROR_NONE;
	}
}




