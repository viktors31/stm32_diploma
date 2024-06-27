#ifndef _OLED_DRIVER_
#define _OLED_DRIVER_

#include "I2C.h"

//Адрес OLED экрана
#define OLED_ADDR 0x3C

//Буфер дисплея (128 x 64 = 8192 точек = 1024 байта)
extern uint8_t OLEDBUFF[1024];

//Координаты
extern uint8_t OLED_CurrentX;
extern uint8_t OLED_CurrentY;

//Шрифт
typedef struct {
	const uint8_t w;                
	const uint8_t h;               
	const uint16_t *const data;         
    const uint8_t *const char_width;
} Font_t;

//Отправка команды дисплею
void OLED_SendCommand(uint8_t command);
//Отправка данных дисплею
void OLED_SendData(uint8_t* data, uint16_t data_size);
//Инициализация OLED
void OLED_Init();
//Включить дисплей
void OLED_On();
//Выключить дисплей
void OLED_Off();
//Установка констранстности (0-255)
void OLED_SetContrast(uint8_t contrast);
//Заполнить дисплей
void OLED_Fill(uint8_t filler);
//Обновить содержимое дисплея
void OLED_Update();
//Отрисовка пикселя на координатах x,y
void OLED_DrawPixel(uint8_t x, uint8_t y, uint8_t set);
//Отрисовка символа
char OLED_DrawChar(char c, Font_t font);
//Вывод строки
char OLED_WriteStr(char* str, Font_t font);
//Установка курсора
void OLED_SetCursor(uint8_t x, uint8_t y);
//Отрисовка линии
void OLED_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
//Отрисовка квадрата
void OLED_DrawRectangle(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
//Очистка дисплея
void OLED_Clear();
//Отрисовка Bitmap изображения, заданного массивом
void OLED_DrawBitmap(uint8_t* img_bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h);


#endif