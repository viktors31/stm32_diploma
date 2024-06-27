#ifndef _BMP180_Driver_
#define _BMP180_Driver_

#include <stdint.h>
#include "I2C.h"

//I2C адрес модуля
#define BMP_ADDR 0x77
//Константа BMP Pressure Sea Level
#define BMP_PSL 101325

//Калибровочные данные
typedef struct {
    short AC1;
    short AC2;
    short AC3;
    unsigned short AC4;
    unsigned short AC5;
    unsigned short AC6;
    short B1;
    short B2;
    short B3;
    short MB;
    short MC;
    short MD;
} BMP_CALIBRATIONS_DATA;

//Адреса регистров с калибровками, MSB
extern const uint8_t bmp_cal_reg_m[11];
//Адреса регистров с калибровками, LSB
extern const uint8_t bmp_cal_reg_l[11];

//Точность измерения давления
typedef enum BMP_OCC {
    LOW, STANDART, HIGH, ULTRA
} BMP_OCC;

//Константы с временем ожидания измерения (ms)
extern const uint8_t bmp_pres_delay[4];

//Чтение регистра regist
uint8_t BMP_ReadRegister(uint8_t regist);
//Запись в регистр regist значения data
void BMP_WriteRegister(uint8_t regist, uint8_t data);
//Установка точности измерения теммературы
void BMP_SetOccurancy(uint8_t occur);
//Чтение калибровок в структуру
void BMP_ReadCalibration();
//Получить значение температуры в 0.1 градусах
long BMP_GetTempL();
//Получить значение теммературы в градусах float
float BMP_GetTemp();
//Получить значение атмосферного давления
long BMP_GetPressure();
//Получить высоту над уровнем моря в метрах
long BMP_GetAltitude();
//Программный сброс модуля
void BMP_Reset();

#endif
