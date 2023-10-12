#include <msp430g2553.h>
#include "Sources/Driver/ConfigFile.h"
#include <stdio.h>
/**
 * main.c
 */
Data DS1302;
char result[];
char temp;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
//	Config_System();
////	NRF_Mode_Rx();
//	RX_Mode();
//	Init_Timer();
//
//	while(1){
//
////	    LCD_DS1302();
//
//	    LcdWriteString("Packets Received");
//	    LcdSetPosition(2,1);
//	    LcdWriteString("NRF: ");
//	    LcdSetPosition(2,6);
//	    LcdWriteString(rx_buf);
//	    LcdSetPosition(1,1);
//
//	    __delay_cycles(9000000);
//	};
// 	return 0;
}

//void NRF(){
//    NRF_ReadRegistor(FIFO_STATUS);
//    NRF_Status = SPI_ReceiveData.DataStore[0];
//
//    if(RW_Flag != 0)
//    {
//        NRF_ReceiveData();
//        RW_Flag = 0;
//    }
//
//    DeleteAllData(&SPI_ReceiveData);
//}

void LCD_DS1302(){
            LcdWriteString("Nguyen Tran Kha");
            LcdSetPosition(2,1);
            AddStringData(&DS1302, ReadByteTime(Address_HOURS));
            AddStringData(&DS1302, ":");
            AddStringData(&DS1302, ReadByteTime(Address_MINUTES));
            AddStringData(&DS1302, ":");
            AddStringData(&DS1302, ReadByteTime(Address_SECONDS));
//            AddStringData(&DS1302, " ");
//            AddStringData(&DS1302, ReadByteTime(Address_DATE));
//            AddStringData(&DS1302, "/");
//            AddStringData(&DS1302, ReadByteTime(Address_MONTH));
//            AddStringData(&DS1302, "/");
//            AddStringData(&DS1302, ReadByteTime(Address_YEAR));
            UART_SendString(&DS1302);
            LcdWriteString(DS1302.DataStore);
            LcdSetPosition(1,1);
            DeleteAllData(&DS1302);
            __delay_cycles(1000000);
}

void Init_Timer(){
    TA0CTL |= TASSEL_2 | MC_2 | TAIE | ID_3;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void)
{
    switch (TA0IV){
    case 2:
        break;
    case 4:
        break;
    case 10:
        TOGGLE_BIT(PORT1.Port_Output_Register, 0);
        NRF_ReceiveSW_SPI();
    break;
    }
}
