#include "DHT11_Driver.h"
#include "timer_delay.h"

//Получения данных от DHT11. В случае провала возвращает 0
uint8_t DHT_Get(float* data) {
    //Настройка линии на выход
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER15_Msk, 1 << GPIO_MODER_MODER15_Pos);
    //Установить логический ноль
    CLEAR_BIT(GPIOA->ODR,GPIO_ODR_OD15);
    //Ожидаем 18мс
    HAL_Delay(18);
    //Настройка линии на вход
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER15_Msk, 0 << GPIO_MODER_MODER15_Pos);
    delay_us(50); //Ждем 50мск, после этого датчик уже должен прижать линию
    if (READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk))
        return 0;
    delay_us(80); //Ждем 80 мск, проверяем чтобы линия не была прижата
    if (!READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk))
        return 0;
    //И ждем когда она опустится = начало передачи данных
    while (READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk)) {};
    //Можно приступать к чтению
    uint8_t dht_data[5] = {0};
    for (uint8_t byte_n = 0; byte_n < 5; byte_n++) {
        for (uint8_t bit_n = 7; bit_n != 255; bit_n--) {
            //Ждем пока линия поднимется
            while (!READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk)) {};
            delay_us(30);
            //Если спустя 30мкс линия не в лог. ед. = прислана 1
            if (READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk))
                dht_data[byte_n] |= 1 << bit_n;
            //Ждем пока линия будет на нуле = передача нового бита
            while (READ_BIT(GPIOA->IDR, GPIO_IDR_ID15_Msk)) {};
        }
    }

    if ((uint8_t)(dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3]) == dht_data[4]) {
        data[0] = (float)dht_data[2];
        data[1] = (float)dht_data[0];
        return 1;
    }
    else
        return 0;
}
