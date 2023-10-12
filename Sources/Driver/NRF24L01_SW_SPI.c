/*
 * NRF24L01_SW_SPI.c
 *
 *  Created on: Sep 11, 2023
 *      Author: nguye
 */


#include "NRF24L01_SW_SPI.h"

//**************************************************
// Function: init_io();
// Description:
// flash led one time,chip enable(ready to TX or RX Mode),
// Spi disable,Spi clock line init high
//**************************************************
void init_io(void)
{
  P1DIR |= CE | CSN | SCK_PIN;
  P2DIR |= MOSI_PIN;

  digitalWrite(SCK_PIN, 0);
  digitalWrite(IRQ, 0);
  digitalWrite(CE, 0);
  digitalWrite(CSN, 1);
}

/**************************************************
 * Function: SPI_RW();
 *
 * Description:
 * Writes one unsigned char to nRF24L01, and return the unsigned char read
 * from nRF24L01 during write, according to SPI protocol
 **************************************************/
unsigned char SPI_RW(unsigned char Byte)
{
  unsigned char i;
  for(i=0;i<8;i++)                      // output 8-bit
  {
    if(Byte&0x80)
    {
      digitalWrite(MOSI_PIN, 1);    // output 'unsigned char', MSB to MOSI
    }
    else
    {
      digitalWrite(MOSI_PIN, 0);
    }
    digitalWrite(SCK_PIN, 1);                      // Set SCK high..
    Byte <<= 1;                         // shift next bit into MSB..
    if(digitalRead(MISO_PIN) == 1)
    {
      Byte |= 1;                        // capture current MISO bit
    }
    digitalWrite(SCK_PIN, 0);           // ..then set SCK low again
  }
  return(Byte);                     // return read unsigned char
}
/**************************************************/

/**************************************************
 * Function: SPI_RW_Reg();
 *
 * Description:
 * Writes value 'value' to register 'reg'
/**************************************************/
unsigned char SPI_RW_Reg(unsigned char reg, unsigned char value)
{
  unsigned char status;

  digitalWrite(CSN, 0);                   // CSN low, init SPI transaction
  status = SPI_RW(reg);                   // select register
  SPI_RW(value);                          // ..and write value to it..
  digitalWrite(CSN, 1);                   // CSN high again

  return(status);                   // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Function: SPI_Read();
 *
 * Description:
 * Read one unsigned char from nRF24L01 register, 'reg'
/**************************************************/
unsigned char SPI_Read(unsigned char reg)
{
  unsigned char reg_val;

  digitalWrite(CSN, 0);           // CSN low, initialize SPI communication...
  SPI_RW(reg);                   // Select register to read from..
  reg_val = SPI_RW(0);           // ..then read register value
  digitalWrite(CSN, 1);          // CSN high, terminate SPI communication

  return(reg_val);               // return register value
}
/**************************************************/

/**************************************************
 * Function: SPI_Read_Buf();
 *
 * Description:
 * Reads 'unsigned chars' #of unsigned chars from register 'reg'
 * Typically used to read RX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Read_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
  unsigned char status,i;

  digitalWrite(CSN, 0);                  // Set CSN low, init SPI tranaction
  status = SPI_RW(reg);             // Select register to write to and read status unsigned char

  for(i=0;i<bytes;i++)
  {
    pBuf[i] = SPI_RW(0);    // Perform SPI_RW to read unsigned char from nRF24L01
  }

  digitalWrite(CSN, 1);                   // Set CSN high again

  return(status);                  // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Function: SPI_Write_Buf();
 *
 * Description:
 * Writes contents of buffer '*pBuf' to nRF24L01
 * Typically used to write TX payload, Rx/Tx address
/**************************************************/
unsigned char SPI_Write_Buf(unsigned char reg, unsigned char *pBuf, unsigned char bytes)
{
  unsigned char status,i;

  digitalWrite(CSN, 0);                   // Set CSN low, init SPI tranaction
  status = SPI_RW(reg);             // Select register to write to and read status unsigned char
  for(i=0;i<bytes; i++)             // then write all unsigned char in buffer(*pBuf)
  {
    SPI_RW(*pBuf++);
  }
  digitalWrite(CSN, 1);                  // Set CSN high again
  return(status);                  // return nRF24L01 status unsigned char
}
/**************************************************/

/**************************************************
 * Function: RX_Mode();
 *
 * Description:
 * This function initializes one nRF24L01 device to
 * RX Mode, set RX address, writes RX payload width,
 * select RF channel, datarate & LNA HCURR.
 * After init, CE is toggled high, which means that
 * this device is now ready to receive a datapacket.
/**************************************************/
void RX_Mode(void)
{
  digitalWrite(CE, 0);
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_Write_Buf(WRITE_REG + RX_ADDR_P0, TX_ADDRESS, TX_ADR_WIDTH); // Use the same address on the RX device as the TX device
  SPI_RW_Reg(WRITE_REG + EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
  SPI_RW_Reg(WRITE_REG + EN_RXADDR, 0x01);  // Enable Pipe0
  SPI_RW_Reg(WRITE_REG + RF_CH, 40);        // Select RF channel 40
  SPI_RW_Reg(WRITE_REG + RX_PW_P0, TX_PLOAD_WIDTH); // Select same RX payload width as TX Payload width
  SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
  SPI_RW_Reg(WRITE_REG + CONFIG, 0x0f);     // Set PWR_UP bit, enable CRC(2 unsigned chars) & Prim:RX. RX_DR enabled..
  digitalWrite(CE, 1);                             // Set CE pin high to enable RX device
  //  This device is now ready to receive one packet of 16 unsigned chars payload from a TX device sending to address
  //  '3443101001', with auto acknowledgment, retransmit count of 10, RF channel 40 and datarate = 2Mbps.
}

void NRF_ReceiveSW_SPI(){
    unsigned char status;                         // read register STATUS's value
    status = SPI_Read(STATUS);                         // read register STATUS's value
    if(status&RX_DR)                                                 // if receive data ready (TX_DS) interrupt
    {
        SPI_Read_Buf(RD_RX_PLOAD, rx_buf, TX_PLOAD_WIDTH);             // read playload to rx_buf
        SPI_RW_Reg(FLUSH_RX,0);                                        // clear RX_FIFO
        UART_SendString(rx_buf);
    }
    SPI_RW_Reg(WRITE_REG+STATUS,status);                             // clear RX_DR or TX_DS or MAX_RT interrupt flag
//    NRF = rx_buf[32];
};

void NRF_TransmitSW_SPI();

void digitalWrite(char Pin, char value){
    if(Pin <= 4){
        if(value == 1){
            P2OUT |= Pin;
        }else{
            P2OUT &= ~Pin;
        }

    }else{
        if(value == 1){
            P1OUT |= Pin;
        }else{
            P1OUT &= ~Pin;
        }

    }
};
unsigned char digitalRead(char Pin){
    if(Pin <= 4){
        if(P2IN & Pin){
            return 1;
        }else{
            return 0;
        }
    }else{
        if(P1IN & Pin){
            return 1;
        }else{
            return 0;
        }
    }
};
