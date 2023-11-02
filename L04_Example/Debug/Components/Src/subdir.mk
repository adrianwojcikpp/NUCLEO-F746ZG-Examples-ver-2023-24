################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Components/Src/dio.c \
../Components/Src/led.c \
../Components/Src/led_config.c \
../Components/Src/pwm.c 

OBJS += \
./Components/Src/dio.o \
./Components/Src/led.o \
./Components/Src/led_config.o \
./Components/Src/pwm.o 

C_DEPS += \
./Components/Src/dio.d \
./Components/Src/led.d \
./Components/Src/led_config.d \
./Components/Src/pwm.d 


# Each subdirectory must supply rules for building sources it contributes
Components/Src/%.o Components/Src/%.su Components/Src/%.cyclo: ../Components/Src/%.c Components/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/AW/STM32CubeIDE/workspace_1.13.0/NUCLEO-F746ZG-Examples-ver-2023-24/L04_Example/Components/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Components-2f-Src

clean-Components-2f-Src:
	-$(RM) ./Components/Src/dio.cyclo ./Components/Src/dio.d ./Components/Src/dio.o ./Components/Src/dio.su ./Components/Src/led.cyclo ./Components/Src/led.d ./Components/Src/led.o ./Components/Src/led.su ./Components/Src/led_config.cyclo ./Components/Src/led_config.d ./Components/Src/led_config.o ./Components/Src/led_config.su ./Components/Src/pwm.cyclo ./Components/Src/pwm.d ./Components/Src/pwm.o ./Components/Src/pwm.su

.PHONY: clean-Components-2f-Src

