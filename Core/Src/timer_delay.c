#include "timer_delay.h"


//Задержка в микросекундах
void delay_us(uint32_t us) {
    WRITE_REG(TIM5->CNT, 0x00000000);
    SET_BIT(TIM5->CR1, TIM_CR1_CEN);
    while (READ_REG(TIM5->CNT) < us) {}
    CLEAR_BIT(TIM5->CR1, TIM_CR1_CEN);
}

void Delay_Init() {
    //Частота 84Мгц / 84 = 1 млн тиков/сек = 1 тик в мкс
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM5EN);
    CLEAR_BIT(TIM5->CR1, TIM_CR1_CEN);
    //NVIC_EnableIRQ(TIM2_IRQn);
    WRITE_REG(TIM5->PSC, 83);
    WRITE_REG(TIM5->ARR, 0xFFFFFFF);
    SET_BIT(TIM5->EGR, TIM_EGR_UG);
}
