/*
 * USART.h
 *
 *  Created on: Aug 21, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_UART_H_
#define SOURCES_DRIVER_UART_H_
#include <msp430g2553.h>
#include "stdin.h"
#include "Data.h"

Data TransmitData;



void UART_Init(uint16_t Baudrate);
void UART_SendChar(char *data);
void UART_SendString(char *data);

#endif /* SOURCES_DRIVER_UART_H_ */
