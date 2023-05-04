/*
 * input.c
 *
 *  Created on: Nov 29, 2022
 *      Author: flyozkan
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "input.h"
#include "io.h"
#include "uart.h"
#include "eeprom.h"
#include "irq.h"

pwm_signal_t signal;
pwm_config_t config;

uint32_t led_timeout;

//uint32_t gcr[37] =  {0};

uint32_t get_duty(int32_t period){
    return  3 + ((1000000 * period) / (SystemCoreClock / config.prs)) ;
}

uint32_t MAP(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax, uint32_t au32_OUTmin, uint32_t au32_OUTmax){
    return (uint32_t)((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}

uint8_t is_callibred(uint32_t capture){
    uint16_t diff = abs(config.calibmax - config.calibzero);
    diff = ((diff > 500) ? abs(capture - config.calibzero) : 10);
    return diff<10;
}

void enable_ic(){
    LL_TIM_EnableIT_CC1(IC_TIMER_REGISTER);
    LL_TIM_CC_EnableChannel(IC_TIMER_REGISTER, IC_TIMER_CHANNEL);
    LL_TIM_EnableCounter(IC_TIMER_REGISTER);
    LL_TIM_GenerateEvent_UPDATE(IC_TIMER_REGISTER);
}

void init_input(void){
    enable_ic();
    //receiveDshotDma();

    signal.timout = 1000;
    signal.dmac = 0;
    signal.armed = 0;
    signal.is_calibrate = 0;

#ifdef USE_EEPROM
    if(eeprom_read()==ERROR){//set default
        config.prs = IC_TIMER_REGISTER->PSC + 1;
        config.calibzero = 900;//load eeprom
        config.calibmax = 1900;
        config.ver = EEPROM_CONF_VERSION;
        config.direction = 0;
        config.reverse = 0;
        eeprom_save();
    }
#endif

}


void capture_callback(void) {
    //detectInput();

    while(!signal.armed && signal.dmac==0);
    if(signal.dmac==0)return;

    //uprintf("%d\n", signal.capture);

    uint32_t capture = (signal.capture);

    if(signal.armed){
        if(((capture) < config.calibmax)){
            signal.state = 1;
            signal.pwm = MAP(capture, config.calibzero, config.calibmax, 0, 1990);
            signal.pwm = signal.pwm > 1990 ? 0 : signal.pwm;
        }
        //signal.pwm = signal.capture
    }else if(signal.is_calibrate){//manuel calibrate

        signal.state = 2;
        config.calibleft = (is_callibred(capture) ?  (config.calibleft + 1) : 0);
        if(config.calibleft > 75){
            //calibre is ok.
            signal.armed = 1;
            signal.state = 4;
#ifdef USE_EEPROM
            eeprom_save();
#endif
        }else if(led_timeout > 500){//500ms
            status_led_toggle();
            led_timeout = 0;
        }
        //if(millis_flag())led_timeout++;
        config.calibzero = capture;
        //uprintf("%d %d %d\n", capture, signal.capture, config.calibleft);
    }else{
        signal.state = 0;
        if( capture > 1500){//rdy calibre
            signal.state = 3;
            signal.is_calibrate = 1;
            config.calibmax = capture;
        }else if(capture <= (config.calibzero)){//auto calibrate
            signal.armed = 1;
            signal.state = 4;
        }
    }


    signal.timout = 10;
    signal.dmac  = 0;

    //enable_ic();
    //receiveDshotDma();
}

