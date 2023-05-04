################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/drivers/drv_led.c \
../Core/drivers/drv_scheduler.c \
../Core/drivers/drv_system.c \
../Core/drivers/drv_uart.c \
../Core/drivers/drv_watchdog.c \
../Core/drivers/drv_ws2812.c 

OBJS += \
./Core/drivers/drv_led.o \
./Core/drivers/drv_scheduler.o \
./Core/drivers/drv_system.o \
./Core/drivers/drv_uart.o \
./Core/drivers/drv_watchdog.o \
./Core/drivers/drv_ws2812.o 

C_DEPS += \
./Core/drivers/drv_led.d \
./Core/drivers/drv_scheduler.d \
./Core/drivers/drv_system.d \
./Core/drivers/drv_uart.d \
./Core/drivers/drv_watchdog.d \
./Core/drivers/drv_ws2812.d 


# Each subdirectory must supply rules for building sources it contributes
Core/drivers/%.o Core/drivers/%.su: ../Core/drivers/%.c Core/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=0 -DDATA_CACHE_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-drivers

clean-Core-2f-drivers:
	-$(RM) ./Core/drivers/drv_led.d ./Core/drivers/drv_led.o ./Core/drivers/drv_led.su ./Core/drivers/drv_scheduler.d ./Core/drivers/drv_scheduler.o ./Core/drivers/drv_scheduler.su ./Core/drivers/drv_system.d ./Core/drivers/drv_system.o ./Core/drivers/drv_system.su ./Core/drivers/drv_uart.d ./Core/drivers/drv_uart.o ./Core/drivers/drv_uart.su ./Core/drivers/drv_watchdog.d ./Core/drivers/drv_watchdog.o ./Core/drivers/drv_watchdog.su ./Core/drivers/drv_ws2812.d ./Core/drivers/drv_ws2812.o ./Core/drivers/drv_ws2812.su

.PHONY: clean-Core-2f-drivers

