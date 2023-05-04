/*
 * pwm.h
 *
 *  Created on: Nov 30, 2022
 *      Author: flyozkan
 */

#ifndef INC_PWM_H_
#define INC_PWM_H_

#include "include.h"

#define HNSEC_PER_USEC      10
#define HNSEC_PER_MSEC      10000
#define HNSEC_PER_SEC       10000000
#define HNSEC_PER_MINUTE    (HNSEC_PER_SEC * 60)
#define NSEC_PER_HNSEC      100

// PA10 --- Phase_A_HI
#define A_FET_HI_GPIO   GPIOA
#define A_FET_HI_PIN    LL_GPIO_PIN_10

// PA9 --- Phase_B_HI
#define B_FET_HI_GPIO   GPIOA
#define B_FET_HI_PIN    LL_GPIO_PIN_9

// PA8 --- Phase_C_HI
#define C_FET_HI_GPIO   GPIOA
#define C_FET_HI_PIN    LL_GPIO_PIN_8

// PB1 --- Phase_A_LO
#define A_FET_LO_GPIO   GPIOB
#define A_FET_LO_PIN    LL_GPIO_PIN_1

// PB0 --- Phase_B_LO
#define B_FET_LO_GPIO   GPIOB
#define B_FET_LO_PIN    LL_GPIO_PIN_0

// PA7 --- Phase_C_LO
#define C_FET_LO_GPIO   GPIOA
#define C_FET_LO_PIN    LL_GPIO_PIN_7

#define AFetHiOff()         LL_GPIO_ResetOutputPin(A_FET_HI_GPIO, A_FET_HI_PIN);
#define AFetHiOn()          LL_GPIO_SetOutputPin(A_FET_HI_GPIO, A_FET_HI_PIN);

#define BFetHiOff()         LL_GPIO_ResetOutputPin(B_FET_HI_GPIO, B_FET_HI_PIN);
#define BFetHiOn()          LL_GPIO_SetOutputPin(B_FET_HI_GPIO, B_FET_HI_PIN);

#define CFetHiOff()         LL_GPIO_ResetOutputPin(C_FET_HI_GPIO, C_FET_HI_PIN);
#define CFetHiOn()          LL_GPIO_SetOutputPin(C_FET_HI_GPIO, C_FET_HI_PIN);

#define AFetLoOff()         LL_GPIO_ResetOutputPin(A_FET_LO_GPIO, A_FET_LO_PIN);
#define AFetLoOn()          LL_GPIO_SetOutputPin(A_FET_LO_GPIO, A_FET_LO_PIN);

#define BFetLoOff()         LL_GPIO_ResetOutputPin(B_FET_LO_GPIO, B_FET_LO_PIN);
#define BFetLoOn()          LL_GPIO_SetOutputPin(B_FET_LO_GPIO, B_FET_LO_PIN);

#define CFetLoOff()         LL_GPIO_ResetOutputPin(C_FET_LO_GPIO, C_FET_LO_PIN);
#define CFetLoOn()          LL_GPIO_SetOutputPin(C_FET_LO_GPIO, C_FET_LO_PIN);

typedef enum {
    PHASE_A = 0,
    PHASE_B = 1,
    PHASE_C = 2,
} motorPhase_e;

typedef struct motor_pwm_ {
    uint16_t mot_pwm_hz;
    uint16_t mot_pwm_dt_ns;
    uint8_t running;
    bool comutate;
} motor_pwm;

typedef struct fastPID{
    int32_t error;
    uint32_t Kp;
    uint32_t Ki;
    uint32_t Kd;
    int32_t integral;
    int32_t derivative;
    int32_t last_error;
    int32_t pid_output;
    int32_t integral_limit;
    int32_t output_limit;
}fastPID;

struct motor_pwm_commutation_step
{
    motorPhase_e positive;
    motorPhase_e negative;
    motorPhase_e floating;
};

enum motor_pwm_phase_manip
{
    MOTOR_PWM_MANIP_LOW,
    MOTOR_PWM_MANIP_HIGH,
    MOTOR_PWM_MANIP_FLOATING,
    MOTOR_PWM_MANIP_HALF,
    MOTOR_PWM_MANIP_END_
};


uint8_t get_step_pwm(void);
uint16_t get_timer_pwm_freq(void);
uint16_t get_rpm(void);
uint16_t get_pwm_duty(void);
uint_fast16_t get_pwm_sinus_duty(motorPhase_e phase, uint_fast16_t pwm_val, bool channel);

float pid_calculate(struct fastPID *pidnow, int actual, int target);
void  check_rpm_threshold(void);

void set_timer_autoreload(TIM_TypeDef *TIMx, uint32_t steps);
void set_comutate_freq(uint32_t freq);

void motor_step(uint8_t step, uint_fast16_t pwm_val);

void motor_pwm_init(void);
void motor_pwm_set_freewheeling(void);
void motor_pwm_set_break(void);
void motor_pwm_set_pwm_val(uint32_t duty_cycle);
void motor_pwm_set_step_and_pwm(const struct motor_pwm_commutation_step* step, int pwm_val);
void motor_pwm_beep(int frequency, int duration_msec);

void comutate_timer_callback(void);
void timer_sinus_callback(void);
void comutate_start_motor(void);

void motorTuneInput(uint8_t motorStepDebug);
void motorTuneReady(void);

/**
 * Direct phase control - for self-testing
 */
void motor_pwm_manip(const enum motor_pwm_phase_manip command[MOTOR_NUM_PHASES]);


#endif /* INC_PWM_H_ */
