#include "LED_Driver.h"

uint16_t led_state = {0};

void LED_Init() {
  uint8_t cmd[2] = {3,0};
  I2C_Master_Send(0x70, cmd, 2);
  I2C_Master_Send(0x73, cmd, 2);
  LED_Set(0, 0);
  LED_Set(0, 0);
}

void LED_Set(uint8_t set, uint8_t num) {
    uint8_t cmd[2] = {1, 0};
    switch(num) {
        case 0:
            led_state &= 0b1111111100011111;
            led_state |= ((set & 0b100)<<3) | ((set & 0b010)<<5) | ((set & 1)<<7);
            cmd[1] = led_state & 0xFF;
            I2C_Master_Send(0x70, cmd, 2);
            break;
        case 1:
            led_state &= 0b1111111111100011;
            led_state |= ((set & 0b100) | ((set & 0b010)<<2) | ((set & 1)<<4));
            cmd[1] = led_state & 0xFF;
            I2C_Master_Send(0x70, cmd, 2);
            break;
    }
}

void LED_Volume_Set(uint16_t set) {
    uint8_t cmd[2] = {1, 0};
    //led_state = 0xFFFF;
    uint16_t temp_led_state = 0;
    temp_led_state |= ((set&0x1)<<1) | ((set&0b10)>>1) | ((set&0b100)<<13) | ((set&0b1000)<<11) | ((set&0b10000)<<9) | ((set&0b100000)<<7) | ((set&0b1000000)<<5) | ((set&0b10000000)<<3) | ((set&0b100000000)<<1) | ((set&0b1000000000)>>1);
    temp_led_state = ~temp_led_state;
    led_state = (temp_led_state & 0b1111111100000011) | (led_state & 0b11111100);
    cmd[1] = led_state & 0xFF;
    I2C_Master_Send(0x70, cmd, 2);
    cmd[1] = led_state >> 8;
    I2C_Master_Send(0x73, cmd, 2);
}
