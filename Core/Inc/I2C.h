#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "stm32f4xx.h"
#include <stdio.h>

void I2C_Init();
void I2C_Master_Send(uint8_t addr, uint8_t* data, uint16_t size);
//I2C Master отправка данных с регистром
void I2C_Master_SendReg(uint8_t addr, uint8_t reg_addr, uint8_t* data, uint16_t size);
void I2C_Master_Read(uint8_t addr, uint8_t* data, uint16_t size);
//I2C Master получение данных с регистром
void I2C_Master_ReadReg(uint8_t addr, uint8_t reg_addr, uint8_t* data, uint16_t size);
void I2C_Scan();

#endif