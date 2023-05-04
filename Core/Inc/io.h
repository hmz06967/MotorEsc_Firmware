/*
 * io.h
 *
 *  Created on: Nov 29, 2022
 *      Author: flyozkan
 */

#ifndef INC_IO_H_
#define INC_IO_H_

#include "main.h"

//FUNCTION
//#define TEST_MODE
//#define ADC_SHOW

#ifndef TEST_MODE
 #define USE_EEPROM 1
#else
#define USE_DEBUG 1
#endif

#define LPF_ALPHA 0.9
#define LOWPASS(feedback, new_value) (uint32_t)((1.0f - LPF_ALPHA)*feedback+LPF_ALPHA*new_value)
#define LOWPASS_ALP(feedback, new_value, alpha) (uint32_t)((1.0f - alpha)*feedback+alpha*new_value)
#define  map( x, in_min, in_max, out_min, out_max) ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)
#define READ_PIN(port, pin) (port->IDR & (1 << pin))

//VARIABLE
#define ADCBUFSIZE 6
#define LED_PORT GPIOA
#define LED_GPIO LL_GPIO_PIN_15

#define INTERVAL_TIM TIM16
#define INTERVAL_PERIOD 1 //us

// ADC channel assignments
#define ADC_CHAN_TEMPERATURE      LL_ADC_CHANNEL_TEMPSENSOR // CH16
#define ADC_CHAN_PHASE_BF         LL_ADC_CHANNEL_1
#define ADC_CHAN_PHASE_A          LL_ADC_CHANNEL_2
#define ADC_CHAN_PHASE_B          LL_ADC_CHANNEL_3
#define ADC_CHAN_PHASE_C          LL_ADC_CHANNEL_4
#define ADC_CHAN_VOLTAGE          LL_ADC_CHANNEL_5

#define TARGET_ADC_CHANNEL_MASK ( ADC_CHAN_PHASE_BF | \
                                  ADC_CHAN_PHASE_A | \
                                  ADC_CHAN_PHASE_B | \
                                  ADC_CHAN_PHASE_C | \
                                  ADC_CHAN_TEMPERATURE | \
                                  ADC_CHAN_VOLTAGE)

#define status_led_on() (LL_GPIO_SetOutputPin(LED_PORT, LED_GPIO))
#define status_led_off() (LL_GPIO_ResetOutputPin(LED_PORT, LED_GPIO))
#define status_led_toggle() (LL_GPIO_TogglePin(LED_PORT, LED_GPIO))
//#define micros()    (INTERVAL_TIM->CNT)
//#define millis()    (INTERVAL_TIM->CNT / 1000 / INTERVAL_PERIOD)
//#define millis_flag()  ((INTERVAL_TIM->CNT % (999 / INTERVAL_PERIOD))==1)

void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

void io_init(void);
void SystemClock_Config(void);
void Error_Handler(void);

#endif /* INC_IO_H_ */
