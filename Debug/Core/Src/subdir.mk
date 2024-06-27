################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADC.c \
../Core/Src/BMP180_Driver.c \
../Core/Src/DHT11_Driver.c \
../Core/Src/GPIO.c \
../Core/Src/I2C.c \
../Core/Src/JR_Driver.c \
../Core/Src/LCD1602_driver.c \
../Core/Src/LED_Driver.c \
../Core/Src/OLED_Driver.c \
../Core/Src/OLED_Font.c \
../Core/Src/RTC_Driver.c \
../Core/Src/Servo.c \
../Core/Src/main.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/timer_delay.c 

OBJS += \
./Core/Src/ADC.o \
./Core/Src/BMP180_Driver.o \
./Core/Src/DHT11_Driver.o \
./Core/Src/GPIO.o \
./Core/Src/I2C.o \
./Core/Src/JR_Driver.o \
./Core/Src/LCD1602_driver.o \
./Core/Src/LED_Driver.o \
./Core/Src/OLED_Driver.o \
./Core/Src/OLED_Font.o \
./Core/Src/RTC_Driver.o \
./Core/Src/Servo.o \
./Core/Src/main.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/timer_delay.o 

C_DEPS += \
./Core/Src/ADC.d \
./Core/Src/BMP180_Driver.d \
./Core/Src/DHT11_Driver.d \
./Core/Src/GPIO.d \
./Core/Src/I2C.d \
./Core/Src/JR_Driver.d \
./Core/Src/LCD1602_driver.d \
./Core/Src/LED_Driver.d \
./Core/Src/OLED_Driver.d \
./Core/Src/OLED_Font.d \
./Core/Src/RTC_Driver.d \
./Core/Src/Servo.d \
./Core/Src/main.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/timer_delay.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADC.cyclo ./Core/Src/ADC.d ./Core/Src/ADC.o ./Core/Src/ADC.su ./Core/Src/BMP180_Driver.cyclo ./Core/Src/BMP180_Driver.d ./Core/Src/BMP180_Driver.o ./Core/Src/BMP180_Driver.su ./Core/Src/DHT11_Driver.cyclo ./Core/Src/DHT11_Driver.d ./Core/Src/DHT11_Driver.o ./Core/Src/DHT11_Driver.su ./Core/Src/GPIO.cyclo ./Core/Src/GPIO.d ./Core/Src/GPIO.o ./Core/Src/GPIO.su ./Core/Src/I2C.cyclo ./Core/Src/I2C.d ./Core/Src/I2C.o ./Core/Src/I2C.su ./Core/Src/JR_Driver.cyclo ./Core/Src/JR_Driver.d ./Core/Src/JR_Driver.o ./Core/Src/JR_Driver.su ./Core/Src/LCD1602_driver.cyclo ./Core/Src/LCD1602_driver.d ./Core/Src/LCD1602_driver.o ./Core/Src/LCD1602_driver.su ./Core/Src/LED_Driver.cyclo ./Core/Src/LED_Driver.d ./Core/Src/LED_Driver.o ./Core/Src/LED_Driver.su ./Core/Src/OLED_Driver.cyclo ./Core/Src/OLED_Driver.d ./Core/Src/OLED_Driver.o ./Core/Src/OLED_Driver.su ./Core/Src/OLED_Font.cyclo ./Core/Src/OLED_Font.d ./Core/Src/OLED_Font.o ./Core/Src/OLED_Font.su ./Core/Src/RTC_Driver.cyclo ./Core/Src/RTC_Driver.d ./Core/Src/RTC_Driver.o ./Core/Src/RTC_Driver.su ./Core/Src/Servo.cyclo ./Core/Src/Servo.d ./Core/Src/Servo.o ./Core/Src/Servo.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su ./Core/Src/timer_delay.cyclo ./Core/Src/timer_delay.d ./Core/Src/timer_delay.o ./Core/Src/timer_delay.su

.PHONY: clean-Core-2f-Src

