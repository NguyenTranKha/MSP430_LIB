/*
 * SPI.c
 *
 *  Created on: Sep 5, 2023
 *      Author: nguye
 */

#include "SPI.h"
#include "UART.h"

void SPI_Init(){

    P1SEL2 |= SPI_CLK | SPI_MISO | SPI_MOSI;
    P1SEL  |= SPI_CLK | SPI_MISO | SPI_MOSI;

    UCB0CTL1 |= UCSWRST;
    //capture data in first egde and change data next edge --- in active state in low
    UCB0CTL0 |= UCMSB | UCMST | UCSYNC | UCCKPH;
    UCB0CTL1 |= UCSSEL_2;
    UCB0BR0 = 12;
    UCB0CTL1 &= ~(UCSWRST);
    IE2 |= UCB0RXIE;
}

void SPI_SendByte(char *data){
    while (!(IFG2 & UCB0TXIFG));
    UCB0TXBUF = *data;;
}

/*#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
    if(IFG2&UCA0RXIFG){
        while(!(IFG2&UCA0RXIFG));
//        AddCharData(&UART_ReceiveData, &UCA0RXBUF);
        AddCharData(&NRF_TransmistData, &UCA0RXBUF);
    }else{
        AddCharData(&SPI_ReceiveData, &UCB0RXBUF);
    }
}*/


