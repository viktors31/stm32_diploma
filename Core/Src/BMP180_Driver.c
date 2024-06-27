#include "BMP180_Driver.h"
#include "timer_delay.h"
#include <math.h>

BMP_CALIBRATIONS_DATA bmp_cal;
BMP_OCC bmp_occ = STANDART;

//Адреса регистров с калибровками, MSB
const uint8_t bmp_cal_reg_m[11] = {0xAA, 0xAC, 0xAE, 0xB0, 0xB2, 0xB4, 0xB6, 0xB8, 0xBA, 0xBC, 0xBE};
//Адреса регистров с калибровками, LSB
const uint8_t bmp_cal_reg_l[11] = {0xAB, 0xAD, 0xAF, 0xB1, 0xB3, 0xB5, 0xB7, 0xB9, 0xBB, 0xBD, 0xBF};
//Константы с временем ожидания измерения (ms)
const uint8_t bmp_pres_delay[4] = {5, 8, 14, 26};

//Чтение регистра register. Возвращает значение регистра
uint8_t BMP_ReadRegister(uint8_t regist) {
    uint8_t data;
    I2C_Master_Send(BMP_ADDR, &regist, 1);
    I2C_Master_Read(BMP_ADDR, &data, 1);
    return data;
}

//Запись значения data в регистер register
void BMP_WriteRegister(uint8_t regist, uint8_t data) {
    uint8_t writeline[2] = {regist, data};
    I2C_Master_Send(BMP_ADDR, writeline, 2);
}

//Установка точности измерения давления
void BMP_SetOccurancy(uint8_t occur) {
    bmp_occ = occur;
}

//Считать калибровки сенсора. Записывает в структуру
void BMP_ReadCalibration() {
    bmp_cal.AC1 = (BMP_ReadRegister(bmp_cal_reg_m[0]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[0]);
    bmp_cal.AC2 = (BMP_ReadRegister(bmp_cal_reg_m[1]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[1]);
    bmp_cal.AC3 = (BMP_ReadRegister(bmp_cal_reg_m[2]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[2]);
    bmp_cal.AC4 = (BMP_ReadRegister(bmp_cal_reg_m[3]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[3]);
    bmp_cal.AC5 = (BMP_ReadRegister(bmp_cal_reg_m[4]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[4]);
    bmp_cal.AC6 = (BMP_ReadRegister(bmp_cal_reg_m[5]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[5]);
    bmp_cal.B1 = (BMP_ReadRegister(bmp_cal_reg_m[6]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[6]);
    bmp_cal.B2 = (BMP_ReadRegister(bmp_cal_reg_m[7]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[7]);
    bmp_cal.MB = (BMP_ReadRegister(bmp_cal_reg_m[8]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[8]);
    bmp_cal.MC = (BMP_ReadRegister(bmp_cal_reg_m[9]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[9]);
    bmp_cal.MD = (BMP_ReadRegister(bmp_cal_reg_m[10]) << 8) | BMP_ReadRegister(bmp_cal_reg_l[10]);
}

//Получить значение температуры. Возвращает значение 0.1 градуса цельсия
long BMP_GetTempL() {
    BMP_WriteRegister(0xF4, 0x2E);
    delay_us(4500);
    long UT = (BMP_ReadRegister(0xF6) << 8) | BMP_ReadRegister(0xF7);
    long x1 = (UT - bmp_cal.AC6) * bmp_cal.AC5 / (1 << 15);
    long x2 = bmp_cal.MC * (1 << 11) / (x1 + bmp_cal.MD);
    long b5 = x1 + x2;
    long temp = (b5 + 8) / (1 << 4);
    return temp;
}

//Получить значение температуры. Возвращает значение float
float BMP_GetTemp() {
    return BMP_GetTempL() / 10.0;
}

//Получить значение атмосферного давления. Возвращает значение в паскалях
long BMP_GetPressure() {
    BMP_WriteRegister(0xF4, 0x2E);
    delay_us(4500);
    long UT = (BMP_ReadRegister(0xF6) << 8) | BMP_ReadRegister(0xF7);
    BMP_WriteRegister(0xF4, (0x34 | (bmp_occ << 6)));
    HAL_Delay(bmp_pres_delay[bmp_occ]);
    delay_us(bmp_pres_delay[bmp_occ] * 1000);
    long UP = (((BMP_ReadRegister(0xF6)) << 16) | ((BMP_ReadRegister(0xF7)) << 8) | BMP_ReadRegister(0xF8)) >> (8 - bmp_occ);
    long x1 = (UT - bmp_cal.AC6) * bmp_cal.AC5 / (1 << 15);
    long x2 = bmp_cal.MC * (1 << 11) / (x1 + bmp_cal.MD);
    long b5 = x1 + x2;
    long b6 = b5 - 4000;
    x1 = (bmp_cal.B2 * (b6 * b6 / (1 << 12))) / (1 << 11);
    x2 = bmp_cal.AC2 * b6 / (1 << 11);
    long x3 = x1 + x2;
    long b3 = ((((long)bmp_cal.AC1 * 4 + x3) << bmp_occ) + 2) / 4;
    x1 = bmp_cal.AC3 * b6 / (1 << 13);
    x2 = (bmp_cal.B1 * (b6 * b6 / (1 << 12))) / (1 << 16);
    x3 = ((x1 + x2) + 2) / 4;
    unsigned long b4 = bmp_cal.AC4 * (unsigned long)(x3 + 32768) / (1 << 15);
    unsigned long b7 = ((unsigned long)UP - b3) * (50000 >> bmp_occ);
    long p;
    if (b7 < 0x80000000)
        p = (b7 * 2) / b4;
    else
        p = (b7 / b4) * 2;
    x1 = (p / (1 << 8)) / (p / (1 << 8));
    x1 = (x1 * 3038) / (1 << 16);
    x2 = (-7357 * p) / (1 << 16);
    p = p + (x1 + x2 + 3791) / 16;
    return p;
}

//Получить высоту над уровнем моря в метрах
long BMP_GetAltitude() {
    long p = BMP_GetPressure();
    long alt = 44330 * (1 - powf(((float)p/BMP_PSL), 1.0/5.255));
    return alt;
}

//Программный сброс модуля
void BMP_Reset() {
    BMP_WriteRegister(0xE0, 0xB6);
}
