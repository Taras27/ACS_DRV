/*
 * common.h
 *
 *  Created on: Dec 17, 2023
 *      Author: Taras Horyn
 */

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "version.h"
#include "flash.h"

typedef struct
{
	GPIO_TypeDef* port;
	UART_HandleTypeDef *uart;
	uint16_t pin;
}RS_485_Data;


typedef struct
{
	volatile uint8_t buffer[24];
	volatile uint8_t data[24];
	volatile uint8_t data_length;
	volatile uint8_t buff_length;
	volatile uint8_t data_to_send;
	volatile uint8_t status;
	volatile uint8_t cmd_type;
	volatile uint8_t cmd;

}RESPONCE_Data;

typedef enum
{

    DRV_SUCCESS		= 0x00, //ok
	ERROR_LENGTH	= 0x01, //ok
	ERROR_DATA		= 0x02, //ok
	ERROR_CMD		= 0x03, //ok
	ERROR_CHECKSUM	= 0x04, //ok
	ERROR_ADDRESS	= 0x05, //ok
	ERROR_TIMEOUT	= 0x06,
	ERROR_BAD_PARAM	= 0x07,
	ERROR_UNKNOWN 	= 0x08
} DRV_Status;

typedef enum
{
	CMD_TYPE_SET = 0x01,
	CMD_TYPE_GET = 0x02
}THERMO_CmdType;

typedef enum
{
	CMD_SET_BaudRate 		= 0x10,
	CMD_SET_WordLength 		= 0x11,
	CMD_SET_StopBit 		= 0x12,
	CMD_SET_Parity 			= 0x13,
	CMD_SET_UartSettings 	= 0x14,
	CMD_SET_Addr 			= 0x15,

	CMD_SET_Default			= 0xF0
}THERMO_CmdSetType;

typedef enum
{
	CMD_GET_Temperature 	= 0x01,
	CMD_GET_Humidity	 	= 0x02,
	CMD_GET_TemperHumidity 	= 0x03,
	CMD_GET_Status		 	= 0x04,

	CMD_GET_BaudRate 		= 0xE0,
	CMD_GET_WordLength 		= 0xE1,
	CMD_GET_StopBit 		= 0xE2,
	CMD_GET_Parity 			= 0xE3,
	CMD_GET_UartSettings 	= 0xE4,
	CMD_GET_Address 		= 0xE5,

	CMD_GET_FwVersion 		= 0xF0,
	CMD_GET_HwVersion 		= 0xF1,
	CND_GET_McuID			= 0xF2,
	CMD_GET_SerialNumber 	= 0xF3,
	CMD_GET_ServiceData		= 0xF4
}THERMO_CmdGetType;

typedef struct
{
	volatile uint8_t data[24];
	volatile uint8_t len;
	volatile THERMO_CmdType cmd_type;
	volatile uint8_t cmd;
}THERMO_Packet;

typedef struct
{
	 FLASH_Data *current_settings;
	 FLASH_Data *default_settings;
	 VERSION_Data *version;
	 SHT20_Data *sht20_data;
	 RESPONCE_Data *packet;
}COMMON_Data;

#endif /* INC_COMMON_H_ */
