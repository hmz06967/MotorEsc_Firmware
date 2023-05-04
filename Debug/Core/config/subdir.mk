################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/config/cli.c \
../Core/config/config.c \
../Core/config/config_eeprom.c 

OBJS += \
./Core/config/cli.o \
./Core/config/config.o \
./Core/config/config_eeprom.o 

C_DEPS += \
./Core/config/cli.d \
./Core/config/config.d \
./Core/config/config_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
Core/config/%.o Core/config/%.su: ../Core/config/%.c Core/config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=0 -DDATA_CACHE_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-config

clean-Core-2f-config:
	-$(RM) ./Core/config/cli.d ./Core/config/cli.o ./Core/config/cli.su ./Core/config/config.d ./Core/config/config.o ./Core/config/config.su ./Core/config/config_eeprom.d ./Core/config/config_eeprom.o ./Core/config/config_eeprom.su

.PHONY: clean-Core-2f-config

