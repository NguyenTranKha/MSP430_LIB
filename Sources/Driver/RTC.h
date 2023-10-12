/*
 * RTC_DS1302.h
 *
 *  Created on: Sep 3, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_RTC_H_
#define SOURCES_DRIVER_RTC_H_

#include "msp430g2553.h"
#include "stdin.h"

#define CLK_RTC  BIT5
#define DATA_RTC BIT4
#define CE_RTC   BIT3

#define Address_SECONDS           0x80
#define Address_MINUTES           0x82
#define Address_HOURS             0x84
#define Address_DATE              0x86
#define Address_MONTH             0x88
#define Address_DAY               0x8A
#define Address_YEAR              0x8C
#define Address_CONTROL           0x8E
#define Address_TRICKLE           0x90
#define Address_CLOCK_BURST_WRITE 0xBE
#define Address_CLOCK_BURST_READ  0xBF
#define Address_RAMSTART          0xC0
#define Address_RAMEND            0xFC
#define Address_RAM_BURST_WRITE   0xFE
#define Address_RAM_BURST_READ    0xFF

#define INPUT  0
#define OUTPUT 1

#define Pluse_Clock { P2OUT |= CLK_RTC; P2OUT &= ~CLK_RTC;}
#define CHECK_DATA (P2IN & DATA_RTC)
#define Init_IO {P2DIR |= CLK_RTC | CE_RTC | DATA_RTC; P2REN |= CLK_RTC | CE_RTC | DATA_RTC;}
#define EnableRTC P2OUT |= CE_RTC
#define DisableRTC   (P2OUT &= ~(CLK_RTC | CE_RTC | DATA_RTC))
#define DATA_IO(TYPE) (TYPE==0?(P2DIR &= ~DATA_RTC) : (P2DIR |= DATA_RTC))

char *ReadByteTime(int AddressTypeTime);


#endif /* SOURCES_DRIVER_RTC_H_ */
