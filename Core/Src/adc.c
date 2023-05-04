/*
 * adc.c
 *
 *  Created on: Jan 15, 2023
 *      Author: flyozkan
 */


#include "main.h"
#include "adc.h"
#include "io.h"
#include "uart.h"

static struct motor_adc_sample _sample;
extern uint16_t adcValues[ADCBUFSIZE];

void init_adc(void){

}

void printf_adc(void){
    uprintf("T:%d,BF:%d,A:%d,B:%d,C:%d\n", _sample.input_temperature, _sample.bemfdivv, _sample.phase_values[0], _sample.phase_values[1], _sample.phase_values[2]);
}

void adc_update_run(void){
    if(_sample.dma_done){
        // RM 13.9: When sampling internal temperature, the adc sampling time must be > 2 * ts_temp (8 microseconds for F051x)
        _sample.bemfdivv = LOWPASS(_sample.bemfdivv, adcValues[0]);
        _sample.phase_values[0] = LOWPASS(_sample.phase_values[0],adcValues[1]);
        _sample.phase_values[1] = LOWPASS(_sample.phase_values[1],adcValues[2]);
        _sample.phase_values[2] = LOWPASS(_sample.phase_values[2], adcValues[3]);
        _sample.input_temperature = LOWPASS(_sample.input_temperature, adcValues[4]);
        _sample.input_voltage = LOWPASS(_sample.input_voltage, adcValues[5]);
        _sample.dma_done = 0;
    }

}

void updateAdcValues(void){
    _sample.dma_done =1;
}

float get_back_emf_voltage(void){
    return ((_sample.bemfdivv * 3.3f) / 0xFFF) / 0.47f;
}

float motor_adc_get_voltage(void){
    return ((_sample.input_voltage * 3.3f) / 0xFFF) / 0.2444f;
}

float motor_adc_get_temperature(void){
   return __LL_ADC_CALC_TEMPERATURE(3300,_sample.input_temperature,LL_ADC_RESOLUTION_12B);
}

bool get_comutator_value(uint8_t phase){
    if(phase>2)return 0;
    return  _sample.phase_values[phase] > 1500;
}

struct motor_adc_sample motor_adc_get_last_sample(void){
    return _sample;
}
