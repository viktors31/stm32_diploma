#ifndef INC_LCD1602_DRIVER_H_
#define INC_LCD1602_DRIVER_H_

#include <stdint.h>
#include <stdio.h>

#define LCD_ADDR (0x27 << 1) //Адрес дисплея 1602
#define PIN_E_ON (1 << 2) //Пин E для дрыганья
#define LCD_DELAY_PERIOD 5 //Период ожидания

void LCD_SendData(uint8_t data, uint8_t lcd_rs);
void LCD_Init();
void LCD_Backlight(uint8_t state);
void LCD_Print(char *message);
void LCD_Clear();
void LCD_CursorInBegin();
void LCD_SetCursor(uint8_t row, uint8_t col);

#endif
