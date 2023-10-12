/*
 * NRF24L01_SW_SPI.h
 *
 *  Created on: Sep 11, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_NRF24L01_SW_SPI_H_
#define SOURCES_DRIVER_NRF24L01_SW_SPI_H_

#include <msp430g2553.h>
#include "Operator.h"
#include "UART.h"

//---------------------------------------------
//#define TX_ADR_WIDTH    5
//// 5 unsigned chars TX(RX) address width
//#define TX_PLOAD_WIDTH  1
//// 20 unsigned chars TX payload
//---------------------------------------------
#define CE       BIT3
// CE_BIT:   Digital Input     Chip Enable Activates RX or TX mode
#define CSN      BIT4
// CSN BIT:  Digital Input     SPI Chip Select
#define SCK_PIN      BIT5
// SCK BIT:  Digital Input     SPI Clock
#define MOSI_PIN     BIT0
// MOSI BIT: Digital Input     SPI Slave Data Input
#define MISO_PIN     BIT1
// MISO BIT: Digital Output    SPI Slave Data Output, with tri-state option
#define IRQ      BIT2
// IRQ BIT:  Digital Output    Maskable interrupt pin
// IRQ BIT:  Digital Output    Maskable interrupt pin
//*********************************************

// SPI(nRF24L01) commands
#define READ_REG        0x00  // Define read command to register
#define WRITE_REG       0x20  // Define write command to register
#define RD_RX_PLOAD     0x61  // Define RX payload register address
#define WR_TX_PLOAD     0xA0  // Define TX payload register address
#define FLUSH_TX        0xE1  // Define flush TX register command
#define FLUSH_RX        0xE2  // Define flush RX register command
#define REUSE_TX_PL     0xE3  // Define reuse TX payload register command
#define NOP             0xFF  // Define No Operation, might be used to read status register
//***************************************************
#define RX_DR    0x40
#define TX_DS    0x20
#define MAX_RT   0x10
//***************************************************
// SPI(nRF24L01) registers(addresses)
#define CONFIG          0x00  // 'Config' register address
#define EN_AA           0x01  // 'Enable Auto Acknowledgment' register address
#define EN_RXADDR       0x02  // 'Enabled RX addresses' register address
#define SETUP_AW        0x03  // 'Setup address width' register address
#define SETUP_RETR      0x04  // 'Setup Auto. Retrans' register address
#define RF_CH           0x05  // 'RF channel' register address
#define RF_SETUP        0x06  // 'RF setup' register address
#define STATUS          0x07  // 'Status' register address
#define OBSERVE_TX      0x08  // 'Observe TX' register address
#define CD              0x09  // 'Carrier Detect' register address
#define RX_ADDR_P0      0x0A  // 'RX address pipe0' register address
#define RX_ADDR_P1      0x0B  // 'RX address pipe1' register address
#define RX_ADDR_P2      0x0C  // 'RX address pipe2' register address
#define RX_ADDR_P3      0x0D  // 'RX address pipe3' register address
#define RX_ADDR_P4      0x0E  // 'RX address pipe4' register address
#define RX_ADDR_P5      0x0F  // 'RX address pipe5' register address
#define TX_ADDR         0x10  // 'TX address' register address
#define RX_PW_P0        0x11  // 'RX payload width, pipe0' register address
#define RX_PW_P1        0x12  // 'RX payload width, pipe1' register address
#define RX_PW_P2        0x13  // 'RX payload width, pipe2' register address
#define RX_PW_P3        0x14  // 'RX payload width, pipe3' register address
#define RX_PW_P4        0x15  // 'RX payload width, pipe4' register address
#define RX_PW_P5        0x16  // 'RX payload width, pipe5' register address
#define FIFO_STATUS     0x17  // 'FIFO Status Register' register address

#define TX_ADR_WIDTH    5   // 5 unsigned chars TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 32 unsigned chars TX payload

static unsigned char TX_ADDRESS[TX_ADR_WIDTH]  =
{
  0x21,0x07,0x19,0x97,0xFA
};

unsigned char rx_buf[TX_PLOAD_WIDTH];
char tx_buf[TX_PLOAD_WIDTH];

void TX_Mode(void);
void RX_Mode(void);
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes);
unsigned char SPI_Read(unsigned char reg);
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value);
unsigned char SPI_RW(unsigned char Byte);
void init_io(void);
void NRF_ReceiveSW_SPI();
void NRF_TransmitSW_SPI();
void digitalWrite(char Pin, char value);
unsigned char digitalRead(char Pin);

#endif /* SOURCES_DRIVER_NRF24L01_SW_SPI_H_ */
