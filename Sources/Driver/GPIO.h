/*
 * GPIO.h
 *
 *  Created on: Aug 21, 2023
 *      Author: nguye
 */

#ifndef SOURCES_DRIVER_GPIO_H_
#define SOURCES_DRIVER_GPIO_H_
#include <msp430g2553.h>

typedef struct GPIO_struct{
    uint8_t Port_Input_Register;
    uint8_t Port_Output_Register;
    uint8_t Port_Direction_Register;
    uint8_t Port_InterruptFlag_Register;
    uint8_t Port_InterruptEdgeSelect_Register;
    uint8_t Port_InterruptEnable_Register;
    uint8_t Port_FunctionSelection_Register;
    uint8_t Port_PullUp_PullDown_ResistorEnable_Register;
} GPIO;

typedef struct GPIO_SEL2_struct{
    uint8_t Port1_FunctionSelection2_Register;
    uint8_t Port2_FunctionSelection2_Register;
} GPIO_Function;

#define PORT1 (*(GPIO*)&P1IN)
#define PORT2 (*(GPIO*)&P2IN)
#define SelectFunctionPin (*(GPIO_Function*)&P1SEL2)

#endif /* SOURCES_DRIVER_GPIO_H_ */
