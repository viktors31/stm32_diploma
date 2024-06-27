#include "I2C.h"

extern volatile uint32_t timer_counter;

//Инициализация шины I2C 1
void I2C_Init() {
    //Включаем тактирование I2C
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN);
    //Отключаем режим двойной адрессации
    CLEAR_BIT(I2C1->OAR2, I2C_OAR2_ENDUAL);
    //Отключаем общий вызов (от широковещательного)
    CLEAR_BIT(I2C1->CR1, I2C_CR1_ENGC);
    //Включить отложенный отклик
    CLEAR_BIT(I2C1->CR1, I2C_CR1_NOSTRETCH);
    //Отключить модуль
    CLEAR_BIT(I2C1->CR1, I2C_CR1_PE);
    //Скорость тактирования модуля = 48 МгЦ (=APB1!!)
    MODIFY_REG(I2C1->CR2, I2C_CR2_FREQ, 42);
    //Максимальное время подъема в Master-mode (для 100 кГц)
    MODIFY_REG(I2C1->TRISE, I2C_TRISE_TRISE, 42 + 1);
    //Установка часов SCL примерно на 100кГц
    MODIFY_REG(I2C1->CCR, (I2C_CCR_FS | I2C_CCR_DUTY | I2C_CCR_CCR), 210);
    //Адрес микроконтроллера = 0x00
    MODIFY_REG(I2C1->OAR1, I2C_OAR1_ADD0 | I2C_OAR1_ADD1_7 | I2C_OAR1_ADD8_9 | I2C_OAR1_ADDMODE, 0x00004000);
    //Настраиваем на работу I2C, SMBus OFF
    MODIFY_REG(I2C1->CR1, I2C_CR1_SMBUS | I2C_CR1_SMBTYPE | I2C_CR1_ENARP, 0x00000000);
    //Запуск I2C
    SET_BIT(I2C1->CR1, I2C_CR1_PE);
    //Разрешить генерацию ACK после приёма байта
    MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
    //Второй адрес = 0x0
    MODIFY_REG(I2C1->OAR2, I2C_OAR2_ADD2, 0);
}

//I2C Master отправка данных
void I2C_Master_Send(uint8_t addr, uint8_t* data, uint16_t size) {
    //Отключить POS
    CLEAR_BIT(I2C1->CR1, I2C_CR1_POS);
    //Включить генерацию ACK
    MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
    //Генерация START
    SET_BIT(I2C1->CR1, I2C_CR1_START);
    //Ожидаем окончания генерации START
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB)){};
    (void) I2C1->SR1;
    //Передача адреса
    MODIFY_REG(I2C1->DR, I2C_DR_DR, (addr<<1) | 0x00);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR)){};
    (void) I2C1->SR1;
    (void) I2C1->SR2;
    //Передача байтов данных
    for(int i = 0; i < size; i++) {
        MODIFY_REG(I2C1->DR, I2C_DR_DR, data[i]);
        while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE)){};
    }
    //Конец передачи. Генерация STOP
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);
}

//I2C Master отправка данных с регистром
void I2C_Master_SendReg(uint8_t addr, uint8_t reg_addr, uint8_t* data, uint16_t size) {
    //Отключить POS
    CLEAR_BIT(I2C1->CR1, I2C_CR1_POS);
    //Включить генерацию ACK
    MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
    //Генерация START
    SET_BIT(I2C1->CR1, I2C_CR1_START);
    //Ожидаем окончания генерации START
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB)){};
    (void) I2C1->SR1;
    //Передача адреса
    MODIFY_REG(I2C1->DR, I2C_DR_DR, (addr<<1) | 0x00);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR)){};
    (void) I2C1->SR1;
    (void) I2C1->SR2;
    //Передача адреса регистра
    MODIFY_REG(I2C1->DR,  I2C_DR_DR, reg_addr);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE)){};
    //Передача байтов данных
    for(int i = 0; i < size; i++) {
        MODIFY_REG(I2C1->DR, I2C_DR_DR, data[i]);
        while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE)){};
    }
    //Конец передачи. Генерация STOP
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);
}

//I2C Master получение данных
void I2C_Master_Read(uint8_t addr, uint8_t* data, uint16_t size) {
    //Отключить POS
    CLEAR_BIT(I2C1->CR1, I2C_CR1_POS);
    //Включить генерацию ACK
    MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
    //Генерация START
    SET_BIT(I2C1->CR1, I2C_CR1_START);
    //Ожидаем окончания генерации START
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB)){};
    (void) I2C1->SR1;
    //Передача адреса
    MODIFY_REG(I2C1->DR, I2C_DR_DR, (addr<<1) | 0x01);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR)){};
    (void) I2C1->SR1;
    (void) I2C1->SR2;
    //Прием данных
    for(int i = 0; i < size; i++) {
        if(i < (size-1) ) {
            while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE)){};
            data[i] = READ_BIT(I2C1->DR, I2C_DR_DR);
        }
        else {
            CLEAR_BIT(I2C1->CR1, I2C_CR1_ACK);
            SET_BIT(I2C1->CR1, I2C_CR1_STOP);
            while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE)){};
            data[i] = READ_BIT(I2C1->DR, I2C_DR_DR);
        }
    }

    //Конец передачи. Генерация STOP
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);
}

//I2C Master получение данных с регистром
void I2C_Master_ReadReg(uint8_t addr, uint8_t reg_addr, uint8_t* data, uint16_t size) {
    //Отключить POS
    CLEAR_BIT(I2C1->CR1, I2C_CR1_POS);
    //Включить генерацию ACK
    MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
    //Генерация START
    SET_BIT(I2C1->CR1, I2C_CR1_START);
    //Ожидаем окончания генерации START
    while (!READ_BIT(I2C1->SR1, I2C_SR1_SB)){};
    (void) I2C1->SR1;
    //Передача адреса
    MODIFY_REG(I2C1->DR, I2C_DR_DR, (addr<<1) | 0x01);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_ADDR)){};
    (void) I2C1->SR1;
    (void) I2C1->SR2;
    //Передача адреса регистра
    MODIFY_REG(I2C1->DR,  I2C_DR_DR, reg_addr);
    while (!READ_BIT(I2C1->SR1, I2C_SR1_TXE)){};
    //Прием данных
    for(int i = 0; i < size; i++) {
        if(i < (size-1) ) {
            while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE)){};
            data[i] = READ_BIT(I2C1->DR, I2C_DR_DR);
        }
        else {
            CLEAR_BIT(I2C1->CR1, I2C_CR1_ACK);
            SET_BIT(I2C1->CR1, I2C_CR1_STOP);
            while (!READ_BIT(I2C1->SR1, I2C_SR1_RXNE)){};
            data[i] = READ_BIT(I2C1->DR, I2C_DR_DR);
        }
    }

    //Конец передачи. Генерация STOP
    SET_BIT(I2C1->CR1, I2C_CR1_STOP);
}

//Сканнер устройств (вывод в отладку)
void I2C_Scan() {
	printf("Scanning I2C bus...\r\n");
    for (uint16_t i2c_dev_num = 0; i2c_dev_num < 128; i2c_dev_num++) {
        //Отключить POS
        CLEAR_BIT(I2C1->CR1, I2C_CR1_POS);
        //Включить генерацию ACK
        MODIFY_REG(I2C1->CR1, I2C_CR1_ACK, I2C_CR1_ACK);
        //Генерация START
        SET_BIT(I2C1->CR1, I2C_CR1_START);
        //Ожидаем окончания генерации START
        while (!READ_BIT(I2C1->SR1, I2C_SR1_SB)){};
        (void) I2C1->SR1;
        //Передача адреса
        I2C1->DR = i2c_dev_num << 1;
        //MODIFY_REG(I2C1->DR, I2C_DR_DR, (i2c_dev_num << 1) | 0x00);
        //Ждем отзыва
        timer_counter = 250;
        while ((READ_BIT(I2C1->SR1, I2C_SR1_ADDR)==0) && (READ_BIT(I2C1->SR1, I2C_SR1_AF)==0) ){
        	if (!timer_counter)
        		break;
        }
        //Если отозвалось
        if (READ_BIT(I2C1->SR1, I2C_SR1_ADDR)) {
            SET_BIT(I2C1->CR1, I2C_CR1_STOP);
            (void) I2C1->SR1;
            (void) I2C1->SR2;
            char msg[20];
            snprintf(msg, sizeof(msg), "Device 0x%02X\r\n", i2c_dev_num);
            printf(msg);
        }
        else {
            SET_BIT(I2C1->CR1, I2C_CR1_STOP);
            CLEAR_BIT(I2C1->SR1, I2C_SR1_AF);
        }
    }
}
