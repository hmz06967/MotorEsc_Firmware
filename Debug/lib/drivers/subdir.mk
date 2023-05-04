################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/drivers/drv_led.c \
../lib/drivers/drv_scheduler.c \
../lib/drivers/drv_system.c \
../lib/drivers/drv_uart.c \
../lib/drivers/drv_watchdog.c \
../lib/drivers/drv_ws2812.c 

OBJS += \
./lib/drivers/drv_led.o \
./lib/drivers/drv_scheduler.o \
./lib/drivers/drv_system.o \
./lib/drivers/drv_uart.o \
./lib/drivers/drv_watchdog.o \
./lib/drivers/drv_ws2812.o 

C_DEPS += \
./lib/drivers/drv_led.d \
./lib/drivers/drv_scheduler.d \
./lib/drivers/drv_system.d \
./lib/drivers/drv_uart.d \
./lib/drivers/drv_watchdog.d \
./lib/drivers/drv_ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
lib/drivers/%.o lib/drivers/%.su: ../lib/drivers/%.c lib/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../lib -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib-2f-drivers

clean-lib-2f-drivers:
	-$(RM) ./lib/drivers/drv_led.d ./lib/drivers/drv_led.o ./lib/drivers/drv_led.su ./lib/drivers/drv_scheduler.d ./lib/drivers/drv_scheduler.o ./lib/drivers/drv_scheduler.su ./lib/drivers/drv_system.d ./lib/drivers/drv_system.o ./lib/drivers/drv_system.su ./lib/drivers/drv_uart.d ./lib/drivers/drv_uart.o ./lib/drivers/drv_uart.su ./lib/drivers/drv_watchdog.d ./lib/drivers/drv_watchdog.o ./lib/drivers/drv_watchdog.su ./lib/drivers/drv_ws2812.d ./lib/drivers/drv_ws2812.o ./lib/drivers/drv_ws2812.su

.PHONY: clean-lib-2f-drivers

