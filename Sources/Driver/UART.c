/*
 * USART.c
 *
 *  Created on: Aug 28, 2023
 *      Author: nguye
 */

#include <Sources/Driver/UART.h>

void UART_Init(uint16_t Baudrate){
    //P1.1 Rx - P1.2 Tx - Config PINOUT
    P1DIR |= BIT1 | BIT2;
    P1SEL |= BIT1 | BIT2;
    P1SEL2|= BIT1 | BIT2;

    //UART Config
    //Hz = 1.048MHz, Baud rates = 9600
    UCA0CTL1 |= UCSSEL_2 | UCSWRST; //SMCLK
    UCA0MCTL |= UCBRS1;
    UCA0BR0 = 109;
    UCA0CTL1 |= UCSSEL_1;
    UCA0CTL1 &= ~UCSWRST;
    IE2 |= UCA0RXIE;
};

void UART_SendString(char *data){
    while(*data != '\0'){
        UCA0TXBUF = *data;
        while(UCA0STAT&UCBUSY);
        data++;
    }
//    UCA0TXBUF = '\n';
}
