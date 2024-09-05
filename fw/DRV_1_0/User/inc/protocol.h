/*
 * protocol.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Taras Horyn
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_

#include <stdint.h>
#include "common.h"

#define PACKET_DEF_DEV_ADDR					0xC0

#define PACKET_SOP_VALUE                    0x01
#define PACKET_EOP_VALUE                    0x17

#define PACKET_SOP_IDX                      0x00
#define PACKET_SIZE_IDX                     0x01
#define PACKET_DEV_ADDR_IDX					0x02
#define PACKET_CMD_TYPE_IDX					0x03
#define PACKET_CMD_IDX                      0x04
#define PACKET_DATA_IDX                     0x05

#define PACKET_CHECKSUM_LENGTH              0x02

#define PACKET_MIN_LENGTH					0x08

void PROTOCOL_Init(void);
void PROTOCOL_Process(THERMO_Packet *packet, COMMON_Data *data);

#endif /* INC_PROTOCOL_H_ */
