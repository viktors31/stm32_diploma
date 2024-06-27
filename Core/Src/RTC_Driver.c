#include "RTC_Driver.h"
#define TenToBin(x) ((x/10)<<4)|(x%10)
#define BinToTen(x) ((x>>4)*10+(0x0F&x))

void RTC_Set(uint8_t h, uint8_t min, uint8_t s, uint8_t d, uint8_t m, uint8_t y) {
    uint8_t reg[8] = {0};
    //перепись секунд, минут
    reg[1] = TenToBin(s);
    reg[2] = TenToBin(min);
    //перепись часов, установка 24H
    reg[3] = TenToBin(h);
    //Расчет и установка дня недели (+ каждую полночь)
    uint8_t a = (14 - m)/12;
    uint8_t y_a = y - a;
    uint8_t m_a = m + 12*a - 2;
    reg[4] = (d + (31 * m_a) / 12 + y_a + y_a/4 - y_a/100 + y_a/400)%7 + 1;
    //перепись дня, месяца
    reg[5] = TenToBin(d);
    reg[6] = TenToBin(m);
    //перепись года (только последние две)
    reg[7] = TenToBin(y);

    I2C_Master_Send(I2C_RTC_ADDR, reg, 8);
}

void RTC_Read(uint8_t* rtc_data) {
    I2C_Master_Send(I2C_RTC_ADDR, 0, 1);
    I2C_Master_Read(I2C_RTC_ADDR, rtc_data, 7);
    for (int i = 0; i < 7; i++)
        rtc_data[i] = BinToTen(rtc_data[i]);
}

