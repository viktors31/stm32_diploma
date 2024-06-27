#ifndef INC_RTC_DRIVER_H_
#define INC_RTC_DRIVER_H_

#include "stm32f4xx.h"
#include "I2C.h"
#define I2C_RTC_ADDR 0x68

void RTC_Set(uint8_t h, uint8_t min, uint8_t s, uint8_t d, uint8_t m, uint8_t y);
void RTC_Read(uint8_t* rtc_data);

#endif
