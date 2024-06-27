#ifndef _DHT11_DRIVER_
#define _DHT11_DRIVER_

#include "stm32f4xx.h"

//Получения данных от DHT11. В случае провала возвращает 0
uint8_t DHT_Get(float* data);

#endif