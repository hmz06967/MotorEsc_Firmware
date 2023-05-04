/*
 * input.h
 *
 *  Created on: Nov 29, 2022
 *      Author: flyozkan
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include "main.h"

#define IC_TIMER_REGISTER TIM3
#define IC_TIMER_CHANNEL LL_TIM_CHANNEL_CH1
#define INPUT_DMA_CHANNEL LL_DMA_CHANNEL_4

typedef struct pwm_config_t_{
    uint16_t calibzero;
    uint16_t calibmax;
    uint16_t calibleft;
    uint32_t prs;
    uint8_t reverse;
    uint8_t direction;
    uint16_t ver;
    uint8_t chk;//sonda olması gerek!
} pwm_config_t;

typedef struct pwm_signal_t_{
    uint32_t pwm;
    uint8_t state;
    uint8_t armed;
    uint8_t is_calibrate;

    int32_t capture;
    uint32_t capture_buffer[64];
    uint8_t dmac;
    int32_t fall;
    int32_t rise;
    uint16_t timout;
} pwm_signal_t;

uint32_t get_duty(int32_t period);

void init_input(void);
void capture_callback(void);

void detectInput(void);
void changeToInput(void);
void changeToOutput(void);

void sendDshotDma(void);
void receiveDshotDma(void);

void TIM16_IRQHandler(void);

#endif /* INC_INPUT_H_ */
