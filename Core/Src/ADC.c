#include "ADC.h"

//Инициализация АЦП #1
void ADC_Init() {
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_ADC1EN);
    //Установка делителя частоты на 6
    MODIFY_REG(ADC1_COMMON->CCR, ADC_CCR_ADCPRE_Msk, 2 << ADC_CCR_ADCPRE_Pos);
    //Разрешить АЦП
    MODIFY_REG(ADC1->CR2, ADC_CR2_ADON_Msk, 1 << ADC_CR2_ADON_Pos);
    //Установка точности измерения = 12-bit (4096)
    MODIFY_REG(ADC1->CR1, ADC_CR1_RES_Msk, 0 << ADC_CR1_RES_Pos);
    //Установка времени выборки (на все ставим предмакс)
    //Используемые каналы: 0, 1, 2, 8
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP0_Msk, 6 << ADC_SMPR2_SMP0_Pos);
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP1_Msk, 6 << ADC_SMPR2_SMP1_Pos);
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP4_Msk, 6 << ADC_SMPR2_SMP4_Pos);
    MODIFY_REG(ADC1->SMPR2, ADC_SMPR2_SMP8_Msk, 6 << ADC_SMPR2_SMP8_Pos);
    HAL_Delay(10);
    //Установка количества опрашиваемых каналов = 4
    MODIFY_REG(ADC1->JSQR, ADC_JSQR_JL_Msk, 3 << ADC_JSQR_JL_Pos);
    //Установка очереди опроса: 0, 1, 4, 8
    MODIFY_REG(ADC1->JSQR, ADC_JSQR_JSQ1_Msk, 0 << ADC_JSQR_JSQ1_Pos);
    MODIFY_REG(ADC1->JSQR, ADC_JSQR_JSQ2_Msk, 1 << ADC_JSQR_JSQ2_Pos);
    MODIFY_REG(ADC1->JSQR, ADC_JSQR_JSQ3_Msk, 4 << ADC_JSQR_JSQ3_Pos);
    MODIFY_REG(ADC1->JSQR, ADC_JSQR_JSQ4_Msk, 8 << ADC_JSQR_JSQ4_Pos);
    //Включить режим SCAN. За один запуск опрашиваются все каналы!
    MODIFY_REG(ADC1->CR1, ADC_CR1_SCAN_Msk, 1 << ADC_CR1_SCAN_Pos);
}
