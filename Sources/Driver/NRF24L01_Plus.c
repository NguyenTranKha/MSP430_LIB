/*
 * NRF24L01_Plus.c
 *
 *  Created on: Sep 5, 2023
 *      Author: nguye
 */


#include "NRF24L01_Plus.h"


void NRF_SPI_Init(){
    SPI_Init();
    P2OUT &= ~(NRF_CNS | NRF_CE);
    P2DIR |= (NRF_CNS | NRF_CE );

    P2OUT |= NRF_IRQ;
    P2REN |= NRF_IRQ;
    P2IES |= NRF_IRQ;
    P2IE  |= NRF_IRQ;
};

void NRF_ReadRegistor(char Registor){
    NRF_CNS_ENABLE;
    SPI_SendByte(&Registor);
    __delay_cycles(100);
    SPI_SendByte(&Registor);
    __delay_cycles(100);
    NRF_CNS_DISABLE;
};

void NRF_WriteRegistor(char Registor, char Data){
    NRF_CNS_ENABLE;
    SPI_SendByte(&Registor);
    __delay_cycles(100);
    SPI_SendByte(&Data);
    __delay_cycles(100);
    NRF_CNS_DISABLE;
};

void NRF_ReadAddress(char Address, char SizeDataAddress){

    NRF_CNS_ENABLE;
    SPI_SendByte(&Address);
    __delay_cycles(100);
    if(Address == RD_RX_PLOAD) {DeleteAllData(&SPI_ReceiveData);};
    int i;
    for( i = 0; i < SizeDataAddress; i++){
        SPI_SendByte(&i);
        __delay_cycles(100);
    }
    NRF_CNS_DISABLE;
};

void NRF_WriteAddress(char Address, char *Data, char SizeDataAddress){
    NRF_CNS_ENABLE;
    SPI_SendByte(&Address);
    __delay_cycles(100);
    int i;
    for( i = 0; i < SizeDataAddress; i++){
        SPI_SendByte(&Data[i]);
        __delay_cycles(100);
    }
    NRF_CNS_DISABLE;
};

void NRF_Mode_Rx(){
    NRF_CE_DISABLE;

    NRF_WriteAddress(WRITE_REG | TX_ADDR, TrasmitAddress, 5);
    NRF_WriteAddress(WRITE_REG | TX_ADDR, TrasmitAddress, 5);

    NRF_WriteAddress(WRITE_REG | RX_ADDR_P0, ReceiveAddress, 5);

    NRF_WriteRegistor(WRITE_REG | EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
    NRF_WriteRegistor(WRITE_REG | EN_RXADDR, 0x01);  // Enable Pipe0
    NRF_WriteRegistor(WRITE_REG | SETUP_RETR, 0x1A); // 500us + 86us, 10 retrans...
    NRF_WriteRegistor(WRITE_REG | RF_CH, 40);        // Select RF channel 40
    NRF_WriteRegistor(WRITE_REG + RX_PW_P0, 32);
    NRF_WriteRegistor(WRITE_REG | RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
    NRF_WriteRegistor(WRITE_REG | CONFIG, 0x0F);

    NRF_CE_ENABLE;
    DeleteAllData(&SPI_ReceiveData);
};
void NRF_Mode_Tx(){

    NRF_CE_DISABLE;

    NRF_WriteAddress(WRITE_REG | TX_ADDR, TrasmitAddress, 5);
    NRF_WriteAddress(WRITE_REG | TX_ADDR, TrasmitAddress, 5);

    NRF_WriteAddress(WRITE_REG | RX_ADDR_P0, ReceiveAddress, 5);

    NRF_WriteRegistor(WRITE_REG | EN_AA, 0x01);      // Enable Auto.Ack:Pipe0
    NRF_WriteRegistor(WRITE_REG | EN_RXADDR, 0x01);  // Enable Pipe0
    NRF_WriteRegistor(WRITE_REG | SETUP_RETR, 0x1A); // 500us + 86us, 10 retrans...
    NRF_WriteRegistor(WRITE_REG | RF_CH, 40);        // Select RF channel 40
    NRF_WriteRegistor(WRITE_REG | RF_SETUP, 0x07);   // TX_PWR:0dBm, Datarate:2Mbps, LNA:HCURR
    NRF_WriteRegistor(WRITE_REG | CONFIG, 0x0E);

    NRF_CE_ENABLE;
    DeleteAllData(&SPI_ReceiveData);
};

void NRF_SendData(Data *Data){

    NRF_ReadRegistor(FIFO_STATUS); //Check Status
    if(SPI_ReceiveData.DataStore[0]&TX_DS){
        NRF_WriteRegistor(FLUSH_TX,0);
    }
    if(SPI_ReceiveData.DataStore[0]&MAX_RT){
        NRF_WriteRegistor(FLUSH_TX,0);
    }
    NRF_WriteRegistor(WRITE_REG | STATUS, SPI_ReceiveData.DataStore[0]);
    NRF_WriteAddress(WR_TX_PLOAD,Data->DataStore,32);
    DeleteAllData(&SPI_ReceiveData);
};

void NRF_ReceiveData(){
    DeleteAllData(&SPI_ReceiveData);
    NRF_ReadRegistor(STATUS);
    if(SPI_ReceiveData.DataStore[0]&RX_DR)
    {
        NRF_ReadAddress(RD_RX_PLOAD, 32);
        NRF_WriteRegistor(FLUSH_RX,0);
    }
    NRF_WriteRegistor(WRITE_REG+STATUS,SPI_ReceiveData.DataStore[0]);
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
    RW_Flag = 1;
    NRF_WriteRegistor(WRITE_REG+STATUS,NRF_Status);
    P2IFG &= ~NRF_IRQ;
}
