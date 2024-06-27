#ifndef INC_SD_DRIVER_H_
#define INC_SD_DRIVER_H_

#include "stm32f4xx.h"
#include "SPI.h"

//Инициализация портов
void SD_Select();
void SD_Reset();
void SD_SendByte(uint8_t Byte);
uint8_t SD_ReceiveByte();
uint8_t SD_Wait();
int SD_Command(uint8_t command, uint32_t arg);
uint8_t SD_Init();

#endif