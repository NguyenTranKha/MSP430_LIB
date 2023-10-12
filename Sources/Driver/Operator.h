/*
 * Operator.h
 *
 *  Created on: Aug 25, 2023
 *      Author: nguye
 */


#define SET_BIT(PORT, bit) (PORT |= (1 << bit))
#define CLEAR_BIT(PORT, bit) (PORT &= ~(1 << bit))
#define TOGGLE_BIT(PORT, bit) (PORT ^= (1 << bit))
#define GET_BIT(PORT, bit) (PORT &(1 << bit))
#define ShiftRightBit(value, bit) (value |=(1 >> bit))
char* itoa(int value, char* result, int base);
