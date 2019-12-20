################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/buttons.c \
../Src/data_separate.c \
../Src/dma.c \
../Src/eeprom24xx.c \
../Src/gpio.c \
../Src/hc06.c \
../Src/i2c-lcd.c \
../Src/i2c.c \
../Src/lcd_messages.c \
../Src/main.c \
../Src/mode.c \
../Src/stm32f1xx_hal_msp.c \
../Src/stm32f1xx_it.c \
../Src/system_stm32f1xx.c \
../Src/usart.c \
../Src/usb.c 

OBJS += \
./Src/buttons.o \
./Src/data_separate.o \
./Src/dma.o \
./Src/eeprom24xx.o \
./Src/gpio.o \
./Src/hc06.o \
./Src/i2c-lcd.o \
./Src/i2c.o \
./Src/lcd_messages.o \
./Src/main.o \
./Src/mode.o \
./Src/stm32f1xx_hal_msp.o \
./Src/stm32f1xx_it.o \
./Src/system_stm32f1xx.o \
./Src/usart.o \
./Src/usb.o 

C_DEPS += \
./Src/buttons.d \
./Src/data_separate.d \
./Src/dma.d \
./Src/eeprom24xx.d \
./Src/gpio.d \
./Src/hc06.d \
./Src/i2c-lcd.d \
./Src/i2c.d \
./Src/lcd_messages.d \
./Src/main.d \
./Src/mode.d \
./Src/stm32f1xx_hal_msp.d \
./Src/stm32f1xx_it.d \
./Src/system_stm32f1xx.d \
./Src/usart.d \
./Src/usb.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"D:/NEDRET/test2/test2/Inc" -I"D:/NEDRET/test2/test2/Drivers/STM32F1xx_HAL_Driver/Inc" -I"D:/NEDRET/test2/test2/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"D:/NEDRET/test2/test2/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"D:/NEDRET/test2/test2/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


