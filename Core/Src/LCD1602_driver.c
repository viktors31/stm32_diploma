/* Набор исполняемых команд для LCD1602
Используется 4-битный интерфейс
DB7 DB6 DB5 DB4 LED E RW RS
P7  P6  P5  P4  P3 P2 P1 P0 */
#include "LCD1602_driver.h"
#include "timer_delay.h"
#include "I2C.h"
uint8_t LCD_backlight_status = (1 << 3); //Флаг подсветки дисплея

//Отправка байта данных дисплею
void LCD_SendData(uint8_t data, uint8_t lcd_rs) {
    uint8_t upper = data & 0xF0;
    uint8_t lower = (data << 4) & 0xF0;
    uint8_t data_packet[4];
    data_packet[0] = upper|lcd_rs|LCD_backlight_status|PIN_E_ON;
    data_packet[1] = upper|lcd_rs|LCD_backlight_status;
    data_packet[2] = lower|lcd_rs|LCD_backlight_status|PIN_E_ON;
    data_packet[3] = lower|lcd_rs|LCD_backlight_status;

    I2C_Master_Send(0x27, data_packet, sizeof(data_packet));
    delay_us(2000);
    return;
}

//Инициализация дисплея
void LCD_Init() {
	LCD_SendData(0b00110011, 0);
	LCD_SendData(0b00110010, 0);
    LCD_SendData(0x28, 0); //включить + не отобр курсор + не миг курсор
    LCD_SendData(0x08, 0); //Вывод слева-направо, сдвиг экрана выкл
    LCD_SendData(0b00000001, 0); //очистка+курсор в начало
    LCD_SendData(0x06,0);   // установка курсора в начале строки
    LCD_SendData(0x0C, 0);
    LCD_SendData(0x02, 0);
}

//Управление подсветкой дисплея
void LCD_Backlight(uint8_t state) {
    LCD_backlight_status = 0 | (state << 3); //меняем значение P3
    I2C_Master_Send(0x27, &LCD_backlight_status, 1);
}

//Вывод сообщения на экран
void LCD_Print(char *message) {
    while(*message) {
        LCD_SendData((uint8_t)(*message), 1);
        message++;
    }
}

//Установка курсора в начало
void LCD_CursorInBegin() {
        LCD_SendData(0b00000010, 0);
}

//Установка курсора
void LCD_SetCursor(uint8_t row, uint8_t col) {
	//Команда 8 = запись адреса DDRAM
	uint8_t cursor = 0x40*row | col;
	LCD_SendData(0x80 | cursor, 0);
}

//Очистка дисплея
void LCD_Clear() {
    LCD_SendData(0b00000001, 0);
}
