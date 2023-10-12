/*

 * I2C.h
 *
 *  Created on: Aug 31, 2023
 *      Author: nguye
*/


#ifndef SOURCES_DRIVER_I2C_H_
#define SOURCES_DRIVER_I2C_H_

#define SDA_PIN BIT7
#define SCL_PIN BIT6
#define PRESCALE 12

void I2cTransmitInit(unsigned char slaveAddress);
void I2cTransmit(unsigned char slaveAddress, unsigned char byte);

unsigned char I2cNotReady();

#endif /* SOURCES_DRIVER_I2C_H_ */
