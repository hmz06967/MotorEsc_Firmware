################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/motor/motor_adc.c \
../Core/motor/motor_beeper.c \
../Core/motor/motor_comparator.c \
../Core/motor/motor_pwm.c \
../Core/motor/motor_rtctl.c \
../Core/motor/motor_signal.c \
../Core/motor/motor_telemetry.c \
../Core/motor/motor_timer.c 

OBJS += \
./Core/motor/motor_adc.o \
./Core/motor/motor_beeper.o \
./Core/motor/motor_comparator.o \
./Core/motor/motor_pwm.o \
./Core/motor/motor_rtctl.o \
./Core/motor/motor_signal.o \
./Core/motor/motor_telemetry.o \
./Core/motor/motor_timer.o 

C_DEPS += \
./Core/motor/motor_adc.d \
./Core/motor/motor_beeper.d \
./Core/motor/motor_comparator.d \
./Core/motor/motor_pwm.d \
./Core/motor/motor_rtctl.d \
./Core/motor/motor_signal.d \
./Core/motor/motor_telemetry.d \
./Core/motor/motor_timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/motor/%.o Core/motor/%.su: ../Core/motor/%.c Core/motor/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0 -std=gnu11 -g3 -DDEBUG -DSTM32F030x6 -DUSE_FULL_LL_DRIVER -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -DINSTRUCTION_CACHE_ENABLE=0 -DDATA_CACHE_ENABLE=0 -c -I../Core/Inc -I../Drivers/STM32F0xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-motor

clean-Core-2f-motor:
	-$(RM) ./Core/motor/motor_adc.d ./Core/motor/motor_adc.o ./Core/motor/motor_adc.su ./Core/motor/motor_beeper.d ./Core/motor/motor_beeper.o ./Core/motor/motor_beeper.su ./Core/motor/motor_comparator.d ./Core/motor/motor_comparator.o ./Core/motor/motor_comparator.su ./Core/motor/motor_pwm.d ./Core/motor/motor_pwm.o ./Core/motor/motor_pwm.su ./Core/motor/motor_rtctl.d ./Core/motor/motor_rtctl.o ./Core/motor/motor_rtctl.su ./Core/motor/motor_signal.d ./Core/motor/motor_signal.o ./Core/motor/motor_signal.su ./Core/motor/motor_telemetry.d ./Core/motor/motor_telemetry.o ./Core/motor/motor_telemetry.su ./Core/motor/motor_timer.d ./Core/motor/motor_timer.o ./Core/motor/motor_timer.su

.PHONY: clean-Core-2f-motor

