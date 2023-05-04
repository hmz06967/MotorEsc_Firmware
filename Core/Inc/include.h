#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "main.h"

#if !defined(UNUSED)
#define UNUSED(x) (void)(x)
#endif

#define MHZ_TO_HZ(x)                ((x) * 1000000)
#define MOTOR_NUM_PHASES            3
#define MOTOR_NUM_COMMUTATION_STEPS 6

#define MIN(a, b)                   (((a) < (b)) ? (a) : (b))
#define MAX(a, b)                   (((a) > (b)) ? (a) : (b))


#include "irq.h"

/*
#include "common/target.h"


#include "drivers/drv_scheduler.h"
#include "drivers/drv_system.h"
#include "drivers/drv_uart.h"
#include "drivers/drv_led.h"
#include "drivers/drv_watchdog.h"
#include "drivers/drv_ws2812.h"

#include "motor/motor_adc.h"
#include "motor/motor_comparator.h"
#include "motor/motor_pwm.h"
#include "motor/motor_signal.h"
#include "motor/motor_telemetry.h"
#include "motor/motor_timer.h"
#include "motor/motor_rtctl.h"
//#include "motor/motor_rtctl_test.h"
#include "motor/motor_beeper.h"

#include "config/config.h"
#include "config/config_master.h"
#include "config/config_eeprom.h"
*/
