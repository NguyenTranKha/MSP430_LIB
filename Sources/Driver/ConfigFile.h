/*
 * ConfigFile.h
 *
 *  Created on: Aug 25, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_CONFIGFILE_H_
#define SOURCES_DRIVER_CONFIGFILE_H_
#include <msp430g2553.h>
#include <Sources/Driver/LCD.h>
#include <Sources/Driver/UART.h>
#include "stdin.h"
#include "stdlib.h"
#include "Data.h"
#include "Operator.h"
#include "GPIO.h"
#include "Clock.h"
#include "I2C.h"
#include "RTC.h"
//#include "SPI.h"
//#include "NRF24L01_Plus.h"
#include "NRF24L01_SW_SPI.h"


void Config_Clock();
void Config_GPIO();
//bool Config_DMA();
//bool Config_PWM();
//bool Config_SPI();
void Config_UART();
void Config_I2C();
void Config_LCD();
void Config_Interrupt();
void Config_System();


#endif /* SOURCES_DRIVER_CONFIGFILE_H_ */
