/* Управление сервоприводом */
#include "Servo.h"

//Инициализация таймера
void Servo_Init() {
    //Таймер 4. Канал 1. Режим ШИМ (пока счетчик меньше CCR = 1)
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM4EN);
    CLEAR_BIT(TIM4->CR1, TIM_CR1_CEN);
    SET_BIT(TIM4->CCER, TIM_CCER_CC1E); //канал 1 включить на выход
    MODIFY_REG(TIM4->CCMR1, TIM_CCMR1_OC1M_Msk, 6 << TIM_CCMR1_OC1M_Pos); //режим шим1
    WRITE_REG(TIM4->PSC, 83); //1 тик = 1/1000 милисекунды
    WRITE_REG(TIM4->ARR, 3000); //переполнение на 3 милисекундах
    //после протиканья - останавливается, перезапуск ручной
    SET_BIT(TIM4->CR1, TIM_CR1_OPM); //one pulse
    SET_BIT(TIM4->EGR, TIM_EGR_UG); //обновляем все
    SET_BIT(TIM4->CR1, TIM_CR1_UDIS); //событие обновления для загрузки регистров
}

//Установка серво на заданный угол
void Servo_Set(uint16_t angle) {
    //Импульс = 400 тиков + angle * 5.5 тиков
    WRITE_REG(TIM4->CCR1, 400 + angle*11.1);
    //WRITE_REG(TIM4->CCR1, 400);
    WRITE_REG(TIM4->CNT, 0x00000000); //скидывает счетчик
    SET_BIT(TIM4->CR1, TIM_CR1_CEN); //вкл. таймер
}
