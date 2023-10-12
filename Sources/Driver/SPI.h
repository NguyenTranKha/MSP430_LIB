/*
 * SPI.h
 *
 *  Created on: Aug 21, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_SPI_H_
#define SOURCES_DRIVER_SPI_H_
#include <msp430g2553.h>
#include "Data.h"


volatile char command;

#define SPI_CLK     BIT5
#define SPI_MOSI    BIT7
#define SPI_MISO    BIT6


void SPI_Init();
void SPI_SendByte(char *data);


#endif /* SOURCES_DRIVER_SPI_H_ */
