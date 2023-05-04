################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/motor/motor_adc.c \
../lib/motor/motor_beeper.c \
../lib/motor/motor_comparator.c \
../lib/motor/motor_pwm.c \
../lib/motor/motor_rtctl.c \
../lib/motor/motor_signal.c \
../lib/motor/motor_telemetry.c \
../lib/motor/motor_timer.c 

OBJS += \
./lib/motor/motor_adc.o \
./lib/motor/motor_beeper.o \
./lib/motor/motor_comparator.o \
./lib/motor/motor_pwm.o \
./lib/motor/motor_rtctl.o \
./lib/motor/motor_signal.o \
./lib/motor/motor_telemetry.o \
./lib/motor/motor_timer.o 

C_DEPS += \
./lib/motor/motor_adc.d \
./lib/motor/motor_beeper.d \
./lib/motor/motor_comparator.d \
./lib/motor/motor_pwm.d \
./lib/motor/motor_rtctl.d \
./lib/motor/motor_signal.d \
./lib/motor/motor_telemetry.d \
./lib/motor/motor_timer.d 


# Each subdirectory must supply rules for building sources it contributes
lib/motor/%.o lib/motor/%.su: ../lib/motor/%.c lib/motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -I../lib -I../Drivers/STM32F0xx_HAL_Driver/Inc/Legacy -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-lib-2f-motor

clean-lib-2f-motor:
	-$(RM) ./lib/motor/motor_adc.d ./lib/motor/motor_adc.o ./lib/motor/motor_adc.su ./lib/motor/motor_beeper.d ./lib/motor/motor_beeper.o ./lib/motor/motor_beeper.su ./lib/motor/motor_comparator.d ./lib/motor/motor_comparator.o ./lib/motor/motor_comparator.su ./lib/motor/motor_pwm.d ./lib/motor/motor_pwm.o ./lib/motor/motor_pwm.su ./lib/motor/motor_rtctl.d ./lib/motor/motor_rtctl.o ./lib/motor/motor_rtctl.su ./lib/motor/motor_signal.d ./lib/motor/motor_signal.o ./lib/motor/motor_signal.su ./lib/motor/motor_telemetry.d ./lib/motor/motor_telemetry.o ./lib/motor/motor_telemetry.su ./lib/motor/motor_timer.d ./lib/motor/motor_timer.o ./lib/motor/motor_timer.su

.PHONY: clean-lib-2f-motor

