#ifndef _SERVO_DRIVER_
#define _SERVO_DRIVER_

#include "stm32f4xx.h"

//Инициализация таймера
void Servo_Init();
//Установка серво на заданный угол
void Servo_Set(uint16_t angle);

#endif