#ifndef INC_LED_Driver_H_
#define INC_LED_Driver_H_

#include "stm32f4xx.h"
#include <stdio.h>
#include "I2C.h"

void LED_Init();
void LED_Set(uint8_t set, uint8_t num);
void LED_Volume_Set(uint16_t set);

#endif