#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f4xx.h"

//Инициализация шины SPI
void SPI_Init();
void SPI_Transmit(uint8_t* data, uint16_t size);
void SPI_Read(uint8_t* data, uint16_t size);
void SPI_TransmitRead(uint8_t* txData, uint8_t* rxData, uint16_t size);

#endif