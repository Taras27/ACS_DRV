/*
 * flash.c
 *
 *  Created on: Dec 17, 2023
 *      Author: Taras Horyn
 */

#include "flash.h"
#include "stm32f0xx_hal.h"


//Size of struct to write in memory is 24 B -> 0x18

// 32 kB - 32 B
// 0x8000 - 0x20 = 0x7FE0
#define FLASH_ADDR 		0x08007FE0


// End of f070 mcu memory
// Total memory: 32kB -> 0x8000
#define FLASH_ADDR_END 	0x08008000

#define FLASH_KEY		0xAA

#define FLASH_DEF_BAUDRATE		115200
#define FLASH_DEF_WORLDLEN		UART_WORDLENGTH_8B
#define FLASH_DEF_STOPBIT 		UART_STOPBITS_1
#define FLASH_DEF_PARITY 		UART_PARITY_NONE
#define FLASH_DEF_DEV_ADDRESS	0xC0
#define FLASH_DEF_WRITE_COUNT	0x01

static uint8_t FLASH_Erase(uint32_t addr, uint32_t len);

HAL_StatusTypeDef CMD_Res;

static uint8_t FLASH_Erase(uint32_t addr, uint32_t len)
{
	CMD_Res = HAL_FLASH_Unlock();

	for (uint8_t i = 0; i < sizeof(FLASH_Data); i += 4, addr += 4)
	{
			CMD_Res = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, 0xFFFFFFFF);
	}

	CMD_Res = HAL_FLASH_Lock();

	return CMD_Res;
}

void FLASH_DefaultSetInit(FLASH_Data *default_setting)
{
	default_setting->WriteCount = FLASH_DEF_WRITE_COUNT;

	default_setting->BaudRate = FLASH_DEF_BAUDRATE;
	default_setting->WordLength = FLASH_DEF_WORLDLEN;
	default_setting->StopBits = FLASH_DEF_STOPBIT;
	default_setting->Parity = FLASH_DEF_PARITY;
	default_setting->DevAddr = FLASH_DEF_DEV_ADDRESS;

	default_setting->Key = FLASH_KEY;
}

uint8_t FLASH_Write (FLASH_Data *data)
{
	uint32_t addr = FLASH_ADDR;

	uint32_t *pWrite = (uint32_t*) data;

	FLASH_Erase(FLASH_ADDR, sizeof(FLASH_Data));

	CMD_Res = HAL_FLASH_Unlock();

	for (uint8_t i = 0; i < sizeof(FLASH_Data); i += 4, pWrite++, addr += 4)
	{
		CMD_Res = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, *pWrite);
	}

	CMD_Res = HAL_FLASH_Lock();

	return CMD_Res;
}

uint8_t FLASH_Read (FLASH_Data *data)
{
	uint32_t *pWrite = (uint32_t*) data;
	uint32_t addr = FLASH_ADDR;

	for (uint8_t i = 0; i < sizeof(FLASH_Data); i += 4, pWrite++, addr += 4)
	{
		*pWrite = *(uint32_t*) addr;
	}

	return HAL_OK;
}

uint8_t FLASH_Process(FLASH_Data *data, FLASH_Data *default_setting)
{
	FLASH_Data copy_setting;
	uint8_t compareError = 0;

	CMD_Res = FLASH_Read(&copy_setting);

	if (copy_setting.Key != FLASH_KEY)
	{
		CMD_Res = FLASH_Write(default_setting);

		data->WriteCount = default_setting->WriteCount;

		data->BaudRate = default_setting->BaudRate;
		data->WordLength = default_setting->WordLength;
		data->StopBits = default_setting->StopBits;
		data->Parity = default_setting->Parity;
		data->DevAddr = default_setting->DevAddr;

		data->Key = default_setting->Key;
	}
	else
	{

		uint8_t *pWorkingSetting = (uint8_t*) data;
		uint8_t *pFlashCopySetting = (uint8_t*) &copy_setting;

		for (uint8_t i = 0; i < (sizeof(FLASH_Data)); i++, pFlashCopySetting++, pWorkingSetting++)
		{
			if (*pWorkingSetting != *pFlashCopySetting)
			{
				compareError++;
			}
		}

		if (compareError > 0)
		{
			data->WriteCount = ++copy_setting.WriteCount;

			data->BaudRate = copy_setting.BaudRate;
			data->WordLength = copy_setting.WordLength;
			data->StopBits = copy_setting.StopBits;
			data->Parity = copy_setting.Parity;
			data->DevAddr = copy_setting.DevAddr;

			data->Key = default_setting->Key;

			CMD_Res = FLASH_Write(data);
		}
	}
	return CMD_Res;
}
