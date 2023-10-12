/*
 * Clock.h
 *
 *  Created on: Aug 21, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_CLOCK_H_
#define SOURCES_DRIVER_CLOCK_H_

#include <msp430g2553.h>


typedef struct DCOCTL_Struct{
    uint8_t cfg_MOD : 5;
    uint8_t cfg_DCO : 3;
} DCO_Control_Register;


typedef struct BCSCTL1_Struct{
    uint8_t cfg_RSEL : 4;
    uint8_t cfg_DIVA : 2;
    uint8_t cfg_XTS : 1;
    uint8_t cfg_XT2OFF : 1;
} Basic_Clock_System_Control_1_Register;

typedef struct BCSCTL2_Struct{
    uint8_t cfg_DCOR : 1;
    uint8_t cfg_DIVS : 2;
    uint8_t cfg_SELS : 1;
    uint8_t cfg_DIVM : 2;
    uint8_t cfg_SELM : 2;
}Basic_Clock_System_Control_2_Register;

typedef struct BCSCTL3_Struct{
    uint8_t cfg_LFXT1OF : 1;
    uint8_t cfg_XT2OF : 1;
    uint8_t cfg_XCAP : 2;
    uint8_t cfg_LFXT1S : 2;
    uint8_t cfg_XT2S : 2;
}Basic_Clock_System_Control_3_Register;


typedef struct Clock_Struct{
    Basic_Clock_System_Control_3_Register Basic_Clock_System_Control_3_Register;
    uint8_t reveser1;
    uint8_t reveser2;
    DCO_Control_Register DCO_Control_Register;
    Basic_Clock_System_Control_1_Register Basic_Clock_System_Control_1_Register;
    Basic_Clock_System_Control_2_Register Basic_Clock_System_Control_2_Register;

}Clock;


#define Clock (*(Clock*)&BCSCTL3)


#endif /* SOURCES_DRIVER_CLOCK_H_ */
