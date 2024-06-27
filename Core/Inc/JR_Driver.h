#ifndef INC_JDDRIVER_H_
#define INC_JDDRIVER_H_

#include "stm32f4xx.h"
#include <stdint.h>

void Joystick_getCoords(uint16_t* coords);
uint8_t Joystick_button();
uint16_t Regulator_getValue();
uint16_t Mic_getValue();

#endif