/*
 * protocol.c
 *
 *  Created on: Nov 19, 2023
 *      Author: Taras Horyn
 */

#include <string.h>
#include "protocol.h"
#include "crc.h"
#include "transport.h"
#include "protocol_set_cmd.h"
#include "protocol_get_cmd.h"
#include "protocol_err_rsp.h"
#include "common.h"

static THERMO_Status PROTOCOL_ValidatePacket(THERMO_Packet *packet, COMMON_Data *data);
static THERMO_Status PROTOCOL_ValidateFooter(THERMO_Packet *packet);
static THERMO_Status PROTOCOL_ValidateLength(THERMO_Packet *packet);
static THERMO_Status PROTOCOL_ValidateCrc(THERMO_Packet *packet);
static THERMO_Status PROTOCOL_ValidateDevAddress(THERMO_Packet *packet);
static THERMO_Status PROTOCOL_ValidateCmd(THERMO_Packet *packet);
static void PROTOCOL_ClearData(THERMO_Packet *packet);

volatile THERMO_Status status = ERROR_UNKNOWN;

ProtocolSetCmd_s PROTOCOL_CmdSetCallBack =
{
	  SET_BaudRate,
	  SET_WordLength,
	  SET_StopBit,
	  SET_Parity,
	  SET_UartSettings,
	  SET_Addr,
	  SET_DefaultSettings
};

ProtocolGetCmd_s PROTOCOL_CmdGetCallBack =
{
	GET_Temperature,
	GET_Humidity,
	GET_TemperHumidity,
	GET_Status,

	GET_BaudRate,
	GET_WordLength,
	GET_StopBit,
	GET_Parity,
	GET_UartSettings,
	GET_Address,

	GET_FwVersion,
	GET_HwVersion,
	GET_McuID,
	GET_SerialNumber,
	GET_ServiceData
};

static uint8_t CMD_SET_List[] = {
	CMD_SET_BaudRate,
	CMD_SET_WordLength,
	CMD_SET_StopBit,
	CMD_SET_Parity,
	CMD_SET_UartSettings,
	CMD_SET_Addr
};

static uint8_t CMD_GET_List[] =
{
	CMD_GET_Temperature,
	CMD_GET_Humidity,
	CMD_GET_TemperHumidity,
	CMD_GET_Status,
	CMD_GET_BaudRate,
	CMD_GET_WordLength,
	CMD_GET_StopBit,
	CMD_GET_Parity,
	CMD_GET_UartSettings,
	CMD_GET_Address,
	CMD_GET_FwVersion,
	CMD_GET_HwVersion,
	CND_GET_McuID,
	CMD_GET_SerialNumber,
	CMD_GET_ServiceData
};

void PROTOCOL_Init(void)
{
	TRANSPORT_Init();
}

void PROTOCOL_Process(THERMO_Packet *packet, COMMON_Data *data)
{
	status = PROTOCOL_ValidatePacket(packet, data);
	if (status == THERMO_SUCCESS)
	{
		switch (packet->cmd_type)
		{
			case CMD_TYPE_SET:
			{
				switch(packet->cmd)
				{
					case CMD_SET_BaudRate:
					{
						uint16_t temp_baud = (packet->data[PACKET_DATA_IDX] << 8) | packet->data[PACKET_DATA_IDX + 1];
						PROTOCOL_CmdSetCallBack.SET_BaudRate(temp_baud);
					}break;

					case CMD_SET_WordLength:
					{
						PROTOCOL_CmdSetCallBack.SET_WordLength(packet->data[PACKET_DATA_IDX]);

					}break;

					case CMD_SET_StopBit:
					{
						PROTOCOL_CmdSetCallBack.SET_StopBit(packet->data[PACKET_DATA_IDX]);
					}break;

					case CMD_SET_Parity:
					{
						PROTOCOL_CmdSetCallBack.SET_Parity(packet->data[PACKET_DATA_IDX]);
					}break;

					case CMD_SET_UartSettings:
					{
						uint16_t temp_baud = (packet->data[PACKET_DATA_IDX] << 8) | packet->data[PACKET_DATA_IDX + 1];
						uint8_t temp_word_len = packet->data[PACKET_DATA_IDX + 2];
						uint8_t temp_stop_bit = packet->data[PACKET_DATA_IDX + 3];
						uint8_t temp_parity = packet->data[PACKET_DATA_IDX + 4];
						PROTOCOL_CmdSetCallBack.SET_UartSettings(temp_baud, temp_word_len, temp_stop_bit, temp_parity);
					}break;

					case CMD_SET_Addr:
					{
						PROTOCOL_CmdSetCallBack.SET_Addr(packet->data[PACKET_DATA_IDX + 1]);
					}break;
				}
			}break;
			case CMD_TYPE_GET:
			{
				data->packet->cmd_type = (uint8_t)CMD_TYPE_GET;
				switch(packet->cmd)
				{
					case CMD_GET_Temperature:
					{
						data->packet->cmd = CMD_GET_Temperature;
						PROTOCOL_CmdGetCallBack.GET_Temperature(data);

					}break;

					case CMD_GET_Humidity:
					{
						data->packet->cmd = CMD_GET_Humidity;
						PROTOCOL_CmdGetCallBack.GET_Humidity(data);

					}break;

					case CMD_GET_TemperHumidity:
					{
						data->packet->cmd = CMD_GET_TemperHumidity;
						PROTOCOL_CmdGetCallBack.GET_TemperHumidity(data);

					}break;

					case CMD_GET_Status:
					{
						data->packet->cmd = CMD_GET_Status;
						PROTOCOL_CmdGetCallBack.GET_Status(data);

					}break;

					case CMD_GET_BaudRate:
					{
						data->packet->cmd = CMD_GET_BaudRate;
						PROTOCOL_CmdGetCallBack.GET_BaudRate(data);

					}break;

					case CMD_GET_WordLength:
					{
						data->packet->cmd = CMD_GET_WordLength;
						PROTOCOL_CmdGetCallBack.GET_WordLength(data);

					}break;

					case CMD_GET_StopBit:
					{
						data->packet->cmd = CMD_GET_StopBit;
						PROTOCOL_CmdGetCallBack.GET_StopBit(data);

					}break;

					case CMD_GET_Parity:
					{
						data->packet->cmd = CMD_GET_Parity;
						PROTOCOL_CmdGetCallBack.GET_Parity(data);

					}break;

					case CMD_GET_UartSettings:
					{
						data->packet->cmd = CMD_GET_UartSettings;
						PROTOCOL_CmdGetCallBack.GET_UartSettings(data);

					}break;

					case CMD_GET_Address:
					{
						data->packet->cmd = CMD_GET_Address;
						PROTOCOL_CmdGetCallBack.GET_Address(data);

					}break;

					case CMD_GET_FwVersion:
					{
						data->packet->cmd = (uint8_t)CMD_GET_FwVersion;
						PROTOCOL_CmdGetCallBack.GET_FwVersion(data);

					}break;

					case CMD_GET_HwVersion:
					{
						data->packet->cmd = CMD_GET_HwVersion;
						PROTOCOL_CmdGetCallBack.GET_HwVersion(data);

					}break;

					case CND_GET_McuID:
					{
						data->packet->cmd = CND_GET_McuID;
						PROTOCOL_CmdGetCallBack.GET_McuID(data);
					}break;

					case CMD_GET_SerialNumber:
					{
						data->packet->cmd = CMD_GET_SerialNumber;
						PROTOCOL_CmdGetCallBack.GET_SerialNumber(data);

					}break;

					case CMD_GET_ServiceData:
					{
						data->packet->cmd = CMD_GET_ServiceData;
						PROTOCOL_CmdGetCallBack.GET_ServiceData(data);
					}break;
				}
			}break;
		}
	}
	else
	{
		PROTOCOL_ERR_Rsp(data);
	}

	PROTOCOL_ClearData(packet);

}

static THERMO_Status PROTOCOL_ValidatePacket(THERMO_Packet *packet, COMMON_Data *data)
{
	THERMO_Status status = THERMO_SUCCESS;

	status = PROTOCOL_ValidateLength(packet);
	if(status != THERMO_SUCCESS)
	{
		data->packet->status = status;
		PROTOCOL_ClearData(packet);
		return status;
	}

	status = PROTOCOL_ValidateFooter(packet);
	if(status != THERMO_SUCCESS)
	{
		data->packet->status = status;
		PROTOCOL_ClearData(packet);
		return status;
	}

	status = PROTOCOL_ValidateCrc(packet);
	if(status != THERMO_SUCCESS)
	{
		data->packet->status = status;
		PROTOCOL_ClearData(packet);
		return status;
	}

	status = PROTOCOL_ValidateDevAddress(packet);
	if(status != THERMO_SUCCESS)
	{
		data->packet->status = status;
		PROTOCOL_ClearData(packet);
		return status;
	}

	status = PROTOCOL_ValidateCmd(packet);
	if(status != THERMO_SUCCESS)
	{
		data->packet->status = status;
		PROTOCOL_ClearData(packet);
		return status;
	}

	return status;
}

static THERMO_Status PROTOCOL_ValidateCmd(THERMO_Packet *packet)
{
	THERMO_Status status = ERROR_CMD;

	if(packet->data[PACKET_CMD_TYPE_IDX] == CMD_TYPE_SET)
	{
		packet->cmd_type = CMD_TYPE_SET;
		for(uint8_t i = 0; i < sizeof(CMD_SET_List); i++)
		{
			if(packet->data[PACKET_CMD_IDX] == CMD_SET_List[i])
			{
				packet->cmd = CMD_SET_List[i];
				return THERMO_SUCCESS;
			}
		}
	}
	else if (packet->data[PACKET_CMD_TYPE_IDX] == CMD_TYPE_GET)
	{
		packet->cmd_type = CMD_TYPE_GET;
		for (uint8_t i = 0; i < sizeof(CMD_GET_List); i++)
		{
			if (packet->data[PACKET_CMD_IDX] == CMD_GET_List[i])
			{
				packet->cmd = CMD_GET_List[i];
				return THERMO_SUCCESS;
			}
		}
	}
	else
	{
		return status = ERROR_CMD;
	}
	return status;
}

static THERMO_Status PROTOCOL_ValidateDevAddress(THERMO_Packet *packet)
{
	THERMO_Status status = ERROR_ADDRESS;

	//TO DO: need to correct for using "CMD_SET_Addr"
	return status = (packet->data[PACKET_DEV_ADDR_IDX] == PACKET_DEF_DEV_ADDR) ? THERMO_SUCCESS : ERROR_ADDRESS;

}

static THERMO_Status PROTOCOL_ValidateCrc(THERMO_Packet *packet)
{
	static THERMO_Status status = ERROR_CHECKSUM;

	uint16_t temp_packet_crc = (packet->data[PACKET_SIZE_IDX + packet->data[PACKET_SIZE_IDX]] << 8) |
							    packet->data[PACKET_SIZE_IDX + packet->data[PACKET_SIZE_IDX] + 1];

	uint16_t temp_calc_crc = CRC16(&packet->data[PACKET_SOP_IDX], (packet->data[PACKET_SIZE_IDX] + 1));

	return status = (temp_calc_crc == temp_packet_crc) ? THERMO_SUCCESS : ERROR_CHECKSUM;
}

static THERMO_Status PROTOCOL_ValidateLength(THERMO_Packet *packet)
{
	THERMO_Status status = ERROR_LENGTH;

	return status = (packet->len >= PACKET_MIN_LENGTH)
					? THERMO_SUCCESS : ERROR_LENGTH;
}

static THERMO_Status PROTOCOL_ValidateFooter(THERMO_Packet *packet)
{
	THERMO_Status status = ERROR_DATA;

	return status = ((packet->data[PACKET_SOP_IDX] == PACKET_SOP_VALUE) &&
					(packet->data[packet->len - 1] == PACKET_EOP_VALUE))
					? THERMO_SUCCESS : ERROR_DATA;
}

static void PROTOCOL_ClearData(THERMO_Packet *packet)
{
	packet->cmd = 0;
	packet->cmd_type = 0;
	packet->len = 0;
	memset((uint32_t*)packet->data, 0x00, BUFFER_SIZE);
}
