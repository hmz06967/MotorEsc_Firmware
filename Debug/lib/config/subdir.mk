################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/config/cli.c \
../lib/config/config.c \
../lib/config/config_eeprom.c 

OBJS += \
./lib/config/cli.o \
./lib/config/config.o \
./lib/config/config_eeprom.o 

C_DEPS += \
./lib/config/cli.d \
./lib/config/config.d \
./lib/config/config_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
lib/config/%.o lib/config/%.su: ../lib/config/%.c lib/config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../lib -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib-2f-config

clean-lib-2f-config:
	-$(RM) ./lib/config/cli.d ./lib/config/cli.o ./lib/config/cli.su ./lib/config/config.d ./lib/config/config.o ./lib/config/config.su ./lib/config/config_eeprom.d ./lib/config/config_eeprom.o ./lib/config/config_eeprom.su

.PHONY: clean-lib-2f-config

