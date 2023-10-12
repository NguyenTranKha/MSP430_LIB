/*
 * ConfigFile.c
 *
 *  Created on: Aug 25, 2023
 *      Author: nguye
 */
#include "ConfigFile.h"
void Config_Clock(){
    Clock.DCO_Control_Register.cfg_DCO = 3;
    Clock.Basic_Clock_System_Control_1_Register.cfg_RSEL = 7;
    Clock.Basic_Clock_System_Control_1_Register.cfg_XTS = 1;
};

void Config_GPIO(){
    SET_BIT(PORT1.Port_Direction_Register, 0);
};

void Config_System(){
    __bis_SR_register(GIE);
    Config_Clock();
    Config_GPIO();
    UART_Init(9600);
//    NRF_SPI_Init();
    init_io();
    LcdInit();

};
