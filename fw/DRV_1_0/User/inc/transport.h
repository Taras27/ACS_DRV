/*
 * transport.h
 *
 *  Created on: Nov 19, 2023
 *      Author: Taras Horyn
 */

#ifndef INC_TRANSPORT_H_
#define INC_TRANSPORT_H_

#include <stdint.h>

#define BUFFER_SIZE 24

void TRANSPORT_Init(void);
uint8_t TRANSPORT_IsDataAvailable(void);
void TRANSPORT_WriteData(uint8_t *data, uint8_t len);
void TRANSPORT_ReadData(uint8_t *data, uint8_t len);


#endif /* INC_TRANSPORT_H_ */
