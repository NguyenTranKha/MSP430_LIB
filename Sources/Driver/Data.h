/*
 * Data.h
 *
 *  Created on: Aug 30, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_DATA_H_
#define SOURCES_DRIVER_DATA_H_

#include <msp430g2553.h>
#include "stdin.h"
typedef struct Data{
    char DataStore[50];
    int lenght;
} Data;

volatile Data NRF_TransmistData;
//volatile Data NRF_ReceiveData;
volatile Data UART_ReceiveData;
volatile Data SPI_ReceiveData;
static char NRF_Status = 0;
volatile char RW_Flag;
static uint16_t NRF = 0;

void AddCharData(Data *Source, char *Data);
void AddStringData(Data *Source, char *Data);
void DeleteAllData(Data *Source);

#endif /* SOURCES_DRIVER_DATA_H_ */
