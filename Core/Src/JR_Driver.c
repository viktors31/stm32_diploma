/* Программный код для работы с джойстиком и регулятором */
#include "JR_Driver.h"

//Получить координаты джостика
void Joystick_getCoords(uint16_t* coords) {
    MODIFY_REG(ADC1->CR2, ADC_CR2_JSWSTART_Msk, 1 << ADC_CR2_JSWSTART_Pos);
    while (READ_BIT(ADC1->SR, ADC_SR_JEOC_Msk) == 0) {};
    coords[0] = 4096 - READ_REG(ADC1->JDR1);
    coords[1] = READ_REG(ADC1->JDR2);
}

//Возвращает: нажат джостик или нет
uint8_t Joystick_button() {
    return READ_BIT(GPIOA->IDR, GPIO_IDR_ID5_Msk);
}

//Возвращает текущее значение регулятора
uint16_t Regulator_getValue() {
    MODIFY_REG(ADC1->CR2, ADC_CR2_JSWSTART_Msk, 1 << ADC_CR2_JSWSTART_Pos);
    while (READ_BIT(ADC1->SR, ADC_SR_JEOC_Msk) == 0) {}
    return READ_REG(ADC1->JDR3);
}

//Возвращает текущий уровень сигнала с микрофона
uint16_t Mic_getValue() {
    MODIFY_REG(ADC1->CR2, ADC_CR2_JSWSTART_Msk, 1 << ADC_CR2_JSWSTART_Pos);
    while (READ_BIT(ADC1->SR, ADC_SR_JEOC_Msk) == 0) {}
    return READ_REG(ADC1->JDR4);
}
