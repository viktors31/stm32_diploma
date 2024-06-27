#include "OLED_Driver.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>

//Буфер дипсплея
uint8_t OLEDBUFF[1024] = {0};
//Координаты
uint8_t OLED_CurrentX = 0;
uint8_t OLED_CurrentY = 0;

//Отправка команды дисплею
void OLED_SendCommand(uint8_t command) {
    I2C_Master_SendReg(OLED_ADDR, 0x00, &command, 1);
}

//Отправка данных дисплею
void OLED_SendData(uint8_t* data, uint16_t data_size) {
    I2C_Master_SendReg(OLED_ADDR, 0x40, data, data_size);
}

//Инициализация OLED
void OLED_Init() {
    //Коэффициент мультиплексирования = 63. ВЫСОТА 64 пикс
    OLED_SendCommand(0xA8);
    OLED_SendCommand(0x3F);
    //Смещение строк (COM) = 0
    OLED_SendCommand(0xD3);
    OLED_SendCommand(0x00);
    //Начальная строка = 0
    OLED_SendCommand(0x40);
    //Адрес столбца 0 на SEG0. ОТРАЖЕНИЕ ГОРИЗОНТ ВЫКЛ
    OLED_SendCommand(0xA1);
    //Направление сканирования строк. ОТРАЖЕНИЕ ВЕРТИКАЛЬ ВЫКЛ
    OLED_SendCommand(0xC8);
    //Задает порядок прорисовки строк и направление.
    OLED_SendCommand(0xDA);
    OLED_SendCommand(0x12);
    //Установка констрастности
    OLED_SendCommand(0x81);
    OLED_SendCommand(0x7F);
    //Полное включение, отображать из RAM
    OLED_SendCommand(0xA4);
    //Нормальный режим. Выключить инверсию
    OLED_SendCommand(0xA6);
    //Настройка частоты
    OLED_SendCommand(0xD5);
    OLED_SendCommand(0x80);
    //Включить регулятор напряжения
    OLED_SendCommand(0x8D);
    OLED_SendCommand(0x14);
    //Адрессация ГОРИЗОНТАЛЬНАЯ
    OLED_SendCommand(0x20);
    OLED_SendCommand(0x00);
    //Настройка адресов столбцов
    OLED_SendCommand(0x21);
    OLED_SendCommand(0x00);
    OLED_SendCommand(127);
    //Настройка адресов строк
    OLED_SendCommand(0x22);
    OLED_SendCommand(0x00);
    OLED_SendCommand(7);

    //OLED_SendCommand(0xB0);
    //Включить экран
    OLED_SendCommand(0xAF);

    OLED_Fill(0);
    OLED_Update();

    //OLED_SetCursor(0, 0);
}

//Включить дисплей
void OLED_On() {
    OLED_SendCommand(0xAF);
}

//Выключить дисплей
void OLED_Off() {
    OLED_SendCommand(0xAE);
}

//Установка констранстности (0-255)
void OLED_SetContrast(uint8_t contrast) {
    OLED_SendCommand(0x81);
    OLED_SendCommand(contrast);
}

//Заполнить дисплей
void OLED_Fill(uint8_t filler) {
    memset(OLEDBUFF, filler ? 0xFF : 0x00, sizeof(OLEDBUFF));
}

//Обновить содержимое дисплея
void OLED_Update() {
    OLED_SendData(OLEDBUFF, 1024);
}

//Отрисовка пикселя на координатах x,y
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t set) {
    if ((x > 127) | (y > 63))
        return;
    if (set)
        OLEDBUFF[x + (y/8) * 128] |= 1 << (y % 8);
    else
        OLEDBUFF[x + (y/8) * 128] &= ~(1 << (y % 8));
}

//Отрисовка символа
char OLED_DrawChar(char c, Font_t font) {
    uint32_t i, b, j;

    if (c < 32 || c > 126)
        return 0;
    if ((128 < (OLED_CurrentX + font.w)) || (64 < (OLED_CurrentY + font.h)))
        return 0;
    
    for (i = 0; i < font.h; i++) {
        b = font.data[(c - 32) * font.h + i];
        for (j = 0; j < font.w; j++) {
            if ((b << j) & 0x8000)
                OLED_DrawPixel(OLED_CurrentX + j, OLED_CurrentY + i, 1);
            else
                OLED_DrawPixel(OLED_CurrentX + j, OLED_CurrentY + i, 0);
        }
    }
    OLED_CurrentX += font.char_width ? font.char_width[c - 32] : font.w;
    return c;
}

//Вывод строки
char OLED_WriteStr(char* str, Font_t font) {
    while (*str) {
        if (OLED_DrawChar(*str, font) != *str)
            return *str;
        str++;
    }
    return *str;
}

//Установка курсора
void OLED_SetCursor(uint8_t x, uint8_t y) {
    OLED_CurrentX = x;
    OLED_CurrentY = y;
}

//Отрисовка линии
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    int32_t deltaX = abs(x2 - x1);
    int32_t deltaY = abs(y2 - y1);
    int32_t signX = ((x1 < x2) ? 1 : -1);
    int32_t signY = ((y1 < y2) ? 1 : -1);
    int32_t error = deltaX - deltaY;
    int32_t error2;
    
    OLED_DrawPixel(x2, y2, 1);

    while((x1 != x2) || (y1 != y2)) {
        OLED_DrawPixel(x1, y1, 1);
        error2 = error * 2;
        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
    return;
}

//Отрисовка квадрата
void OLED_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
    OLED_DrawLine(x1,y1,x2,y1);
    OLED_DrawLine(x2,y1,x2,y2);
    OLED_DrawLine(x2,y2,x1,y2);
    OLED_DrawLine(x1,y2,x1,y1);
    return;
}

//Очистка дисплея
void OLED_Clear() {
    for (uint16_t i = 0; i < 1024; i++)
        OLEDBUFF[i] = 0;
    OLED_Update();
}

//Отрисовка Bitmap изображения, заданного массивом
void OLED_DrawBitmap(uint8_t* img_bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    int16_t byteWidth = (w + 7) / 8;
    uint8_t byte = 0;

    if (x > 127 || y > 63) {
        return;
    }

    for (uint8_t j = 0; j < h; j++, y++) {
        for (uint8_t i = 0; i < w; i++) {
            if (i & 7) {
                byte <<= 1;
            } else {
                byte = (*(const unsigned char *)(&img_bitmap[j * byteWidth + i / 8]));
            }

            if (byte & 0x80) {
                OLED_DrawPixel(x + i, y, 1);
            }
        }
    }
    return;
}


