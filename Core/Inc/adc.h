/*
 * adc.h
 *
 *  Created on: Jan 15, 2023
 *      Author: flyozkan
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdbool.h>

struct motor_adc_sample
{
    uint64_t timestamp;
    uint32_t bemfdivv;
    uint32_t phase_values[3];
    uint32_t input_voltage;
    uint32_t input_current;
    uint32_t input_temperature;
    uint8_t dma_done;
};

void init_adc(void);
void adc_update_run(void);
void updateAdcValues(void);

bool get_comutator_value(uint8_t phase);
float motor_adc_get_voltage(void);
float get_back_emf_voltage(void);
float motor_adc_get_temperature(void);
struct motor_adc_sample motor_adc_get_last_sample(void);
void printf_adc(void);

#endif /* INC_ADC_H_ */
