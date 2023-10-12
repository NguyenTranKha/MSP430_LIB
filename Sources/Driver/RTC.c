/*
 * RTC.c
 *
 *  Created on: Sep 3, 2023
 *      Author: nguye
 */

#include "RTC.h"

#include "stdin.h"

#include "Operator.h"

char *ReadByteTime(int AddressTypeTime){

        //Start Read
        int i = 0;
        volatile uint8_t result = 0;
        char text[] = "";
        char year__[] = "20";
        char diff[] = "0";
        ++AddressTypeTime;
        Init_IO;
        EnableRTC;


        for (i = 0; i < 8; i++) {
                if (AddressTypeTime & (1 << i)) {
                        P2OUT |= DATA_RTC;
                        Pluse_Clock;
                } else {
                        P2OUT &= ~DATA_RTC;
                        Pluse_Clock;
                }
        }
        DATA_IO(INPUT);

        for (i = 0; i < 8; i++) {
                if (CHECK_DATA) {
                        SET_BIT(result, i);
                        Pluse_Clock;

                } else {
                        Pluse_Clock;
                }
        }
        DisableRTC;
//            __delay_cycles(50000);
        itoa(result, text, 16);
        if(AddressTypeTime == (Address_YEAR+1)){
            strcat(year__,text);
            return year__;
        }else{
            if(result < 10){
                 strcat(diff,text);
                 return diff;
            }else
                return text;
        }
}
