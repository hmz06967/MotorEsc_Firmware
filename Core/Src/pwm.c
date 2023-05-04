#include "pwm.h"
#include "io.h"
#include "adc.h"
#include "comutate.h"
#include "uart.h"

static uint16_t _pwm_max;
static uint16_t _pwm_mid;
static uint16_t _pwm_min;

static uint8_t  _step;
static uint16_t _pwm_duty; // 100 - 1900
static uint16_t _pwm_freq;
static uint16_t _pwm_step;

static uint16_t _comate_freq;

uint8_t backstep = 0;
uint16_t count_com = 120;

uint8_t rising = 1;
uint32_t back_com_time;
uint32_t actual_time;
uint32_t speed_pwm;
uint16_t max_rpm;
uint16_t max_bemf_volt;
uint16_t mosfet_thr = 500;//mv
uint8_t com_block = 14;

/*int16_t pwmSin[] = {
        500,508,516.5,524.5,536,544,552.5,561,569,577.5,586,594,602.5,611,622,630,638.5,647,655,663.5,672,680,686,694,702.5,711,719,727.5,735.5,741.5,749.5,758,763.5,772,780,785.5,794,799.5,808,813.5,822,827.5,833,841,847,852.5,858,866,872,877.5,883,888.5,894,899.5,905,908,913.5,919,924.5,927.5,933,935.5,941,944,949.5,952.5,955,960.5,963.5,966,969,971.5,974.5,977.5,980,983,985.5,985.5,988.5,991,991,994,994,996.5,996.5,996.5,999.5,999.5,999.5,999.5,999.5,999.5,999.5,999.5,996.5,996.5,996.5,994,994,991,991,988.5,985.5,985.5,983,980,977.5,974.5,971.5,969,966,963.5,960.5,955,952.5,949.5,944,941,935.5,933,927.5,924.5,919,913.5,908,905,899.5,894,888.5,883,877.5,872,866,858,852.5,847,841,833,827.5,822,813.5,808,799.5,794,785.5,780,772,763.5,758,749.5,741.5,735.5,727.5,719,711,702.5,694,686,680,672,663.5,655,647,638.5,630,622,611,602.5,594,586,577.5,569,561,552.5,544,536,524.5,516.5,508,500,491.5,483,475,463.5,455.5,447,438.5,430.5,422,413.5,405.5,397,388.5,377.5,369.5,361,352.5,344.5,336,327.5,319.5,313.5,305.5,297,288.5,280.5,272,264,258,250,241.5,236,227.5,219.5,214,205.5,200,191.5,186,177.5,172,166.5,158.5,152.5,147,141.5,133.5,127.5,122,116.5,111,105.5,100,94.5,91.5,86,80.5,75,72,66.5,64,58.5,55.5,50,47,44.5,39,36,33.5,30.5,28,25,22,19.5,16.5,14,14,11,8.5,8.5,5.5,5.5,3,3,3,0,0,0,0,0,0,0,0,0,3,3,3,5.5,5.5,8.5,8.5,11,14,14,16.5,19.5,22,25,28,30.5,33.5,36,39,44.5,47,50,55.5,58.5,64,66.5,72,75,80.5,86,91.5,94.5,100,105.5,111,116.5,122,127.5,133.5,141.5,147,152.5,158.5,166.5,172,177.5,186,191.5,200,205.5,214,219.5,227.5,236,241.5,250,258,264,272,280.5,288.5,297,305.5,313.5,319.5,327.5,336,344.5,352.5,361,369.5,377.5,388.5,397,405.5,413.5,422,430.5,438.5,447,455.5,463.5,475,483,491.5,500
        //180,183,186,189,193,196,199,202, 205,208,211,214,217,220,224,227, 230,233,236,239,242,245,247,250, 253,256,259,262,265,267,270,273, 275,278,281,283,286,288,291,293, 296,298,300,303,305,307,309,312, 314,316,318,320,322,324,326,327, 329,331,333,334,336,337,339,340, 342,343,344,346,347,348,349,350, 351,352,353,354,355,355,356,357, 357,358,358,359,359,359,360,360, 360,360,360,360,360,360,360,359, 359,359,358,358,357,357,356,355, 355,354,353,352,351,350,349,348, 347,346,344,343,342,340,339,337, 336,334,333,331,329,327,326,324, 322,320,318,316,314,312,309,307, 305,303,300,298,296,293,291,288, 286,283,281,278,275,273,270,267, 265,262,259,256,253,250,247,245, 242,239,236,233,230,227,224,220, 217,214,211,208,205,202,199,196, 193,189,186,183,180,177,174,171, 167,164,161,158,155,152,149,146, 143,140,136,133,130,127,124,121, 118,115,113,110,107,104,101,98, 95,93,90,87,85,82,79,77, 74,72,69,67,64,62,60,57, 55,53,51,48,46,44,42,40, 38,36,34,33,31,29,27,26, 24,23,21,20,18,17,16,14, 13,12,11,10,9,8,7,6, 5,5,4,3,3,2,2,1, 1,1,0,0,0,0,0,0, 0,0,0,1,1,1,2,2, 3,3,4,5,5,6,7,8, 9,10,11,12,13,14,16,17, 18,20,21,23,24,26,27,29, 31,33,34,36,38,40,42,44, 46,48,51,53,55,57,60,62, 64,67,69,72,74,77,79,82, 85,87,90,93,95,98,101,104, 107,110,113,115,118,121,124,127, 130,133,136,140,143,146,149,152, 155,158,161,164,167,171,174,177
};*/

motor_pwm motor;

fastPID currentPid = {   // 1khz loop time
       .Kp = 10,
       .Ki = 0,
       .Kd = 100,
       .integral_limit = 10000,
       .output_limit = 50000
};

/*
uint32_t calculate_pwm_sin(uint8_t sine_offset){
    return ((pwmSin[sine_offset] / 360.0f)) * _pwm_step; //get_pwm_duty();
}
*/
static void init_constants(uint16_t frequency, uint16_t pwm_dead_time_ns)
{
    _pwm_freq = frequency;
    _pwm_step = (SystemCoreClock / frequency) - 1;

    _pwm_max = _pwm_step ;//1999
    _pwm_mid = _pwm_max / 2;
    _pwm_min = (uint16_t)((pwm_dead_time_ns / 1e9f) / (1.0f / SystemCoreClock));
    _step = 1;
    _pwm_duty = _pwm_min;

#ifdef DUTY_DMA
    uint16_t dma_length = 360;
    //create pwm
    /*for(uint8_t i=0; i<dma_length; i++){
        pwmSin[i] = calculate_pwm_sin(i);
    }*/

    irq_primask_disable();

    ///DMA
    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t) &(TIM1->CCR1));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_2, (uint32_t)pwmSin);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, dma_length);

    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t) &(TIM1->CCR2));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_3, (uint32_t)pwmSin);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, dma_length);

    LL_DMA_SetPeriphAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t) &(TIM1->CCR3));
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_CHANNEL_5, (uint32_t)pwmSin);
    LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, dma_length);

    LL_TIM_CC_SetDMAReqTrigger(TIM1, LL_TIM_CCDMAREQUEST_CC);

    LL_TIM_EnableDMAReq_CC1(TIM1);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_2);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

    LL_TIM_EnableDMAReq_CC2(TIM1);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_3);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

    LL_TIM_EnableDMAReq_CC3(TIM1);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_CHANNEL_5);
    LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);

    irq_primask_enable();
#endif

    set_timer_autoreload(TIM14, 300);//50HZ
    //LL_TIM_EnableIT_UPDATE(TIM1);
    LL_TIM_OC_SetDeadTime(TIM1, pwm_dead_time_ns);
    LL_TIM_SetAutoReload(TIM1,  _pwm_step);//24kHZ
    LL_TIM_EnableAllOutputs(TIM1);
    LL_TIM_EnableCounter(TIM1);

}

void motor_pwm_init(void) {
    init_constants(24000, 45);//24 khz,  sys_freq/45 ns
    motor_pwm_set_freewheeling();
}

float pid_calculate(struct fastPID *pidnow, int actual, int target){
    pidnow->error = actual - target;
    pidnow->integral = pidnow->integral + pidnow->error*pidnow->Ki + pidnow->last_error*pidnow->Ki;
    if(pidnow->integral > pidnow->integral_limit){
        pidnow->integral = pidnow->integral_limit;
    }
    if(pidnow->integral < -pidnow->integral_limit){
        pidnow->integral = -pidnow->integral_limit;
    }

    pidnow->derivative = pidnow->Kd * (pidnow->error - pidnow->last_error);
    pidnow->last_error = pidnow->error;

    pidnow->pid_output = pidnow->error*pidnow->Kp + pidnow->integral + pidnow->derivative;

    if (pidnow->pid_output>pidnow->output_limit){
        pidnow->pid_output = pidnow->output_limit;
    }if(pidnow->pid_output <-pidnow->output_limit){
        pidnow->pid_output = -pidnow->output_limit;
    }
    return pidnow->pid_output;
}

void  check_rpm_threshold(){
    //_pwm_duty = lpf(input_pwm_duty)//0 - 2000
    //if(_pwm_duty >= (_pwm_max - 10)){
        max_rpm = MAX(max_rpm, get_rpm());
        max_bemf_volt = MAX(max_bemf_volt, get_back_emf_voltage() * 100);
    //}
    if((get_back_emf_voltage() * 100) >= max_bemf_volt){
        //maksimum akımın aktığı minimum duty değeri
        mosfet_thr = MIN(mosfet_thr, ((_pwm_max / _pwm_duty) * (_pwm_max / 10)));//0 - 1000
    }
    /*if(max_rpm>12000){
        uprintf("m_rpm:%d,m_thr:%d,m_bemf:%d\n", max_rpm, mosfet_thr, max_bemf_volt);
    }*/
}

void set_timer_autoreload(TIM_TypeDef *TIMx, uint32_t freq){
    LL_TIM_SetAutoReload(TIMx, (SystemCoreClock / freq)-1);//1khz-1);//HZ
}

void set_comutate_freq(uint32_t freq){
    set_timer_autoreload(TIM14, freq);//comutator
    _comate_freq = freq;
}

uint8_t get_step_pwm(void){
    return _step;
}

uint16_t get_timer_pwm_freq(void){
    return _pwm_freq;
}

uint16_t get_rpm(){
    return (6000000 / (actual_time * (com_block / 2)));
}

static inline void phase_float(motorPhase_e phase){
    switch(phase) {
        case PHASE_A:
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_INACTIVE);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3N);
            //AFetLoOn();
            break;
        case PHASE_B:
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_INACTIVE);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2N);
            //BFetLoOn();
            break;
        case PHASE_C:
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_INACTIVE);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1N);
            //CFetLoOn();
            break;
        default:
            break;
    }
}

static inline void phase_n_pwm(motorPhase_e phase, uint_fast16_t pwm_val){

    switch(phase) {
        case PHASE_A:
           // LL_TIM_OC_SetCompareCH3(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3N);
            //AFetHiOff();
            break;
        case PHASE_B:
            //LL_TIM_OC_SetCompareCH2(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2N);
            //BFetHiOff();
            break;
        case PHASE_C:
            //LL_TIM_OC_SetCompareCH1(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1N);
            //CFetHiOff();
            break;
        default:
            break;
    }
}

static inline void phase_p_pwm(motorPhase_e phase, uint_fast16_t pwm_val){

    switch(phase) {
        case PHASE_A:
            //LL_TIM_OC_SetCompareCH3(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3N);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
            //AFetLoOff();
            break;

        case PHASE_B:
            //LL_TIM_OC_SetCompareCH2(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2N);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
            //BFetLoOff();
            break;

        case PHASE_C:
            //LL_TIM_OC_SetCompareCH1(TIM1, pwm_val);
            LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
            LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1N);
            LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
            //CFetLoOff();
            break;

        default:
            break;
    }
}


static inline void motor_pwm_stop(void)
{

    LL_TIM_OC_SetCompareCH1(TIM1, _pwm_mid);
    LL_TIM_OC_SetCompareCH2(TIM1, _pwm_mid);
    LL_TIM_OC_SetCompareCH3(TIM1, _pwm_mid);

    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1N);

    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2N);

    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3N);

    /* Generate TIM1 COM event by software */
    LL_TIM_GenerateEvent_COM(TIM1);
}

static void motor_pwm_brake(void)
{
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH1N);

    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH2N);

    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_FORCED_INACTIVE);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3);
    LL_TIM_CC_DisableChannel(TIM1, LL_TIM_CHANNEL_CH3N);

    /* Generate TIM1 COM event by software */
    LL_TIM_GenerateEvent_COM(TIM1);
}


void motor_step(uint8_t step, uint_fast16_t pwm_val){

    switch (step) {
        case 1:
            phase_p_pwm(PHASE_A, pwm_val);
            phase_n_pwm(PHASE_B, pwm_val);
            phase_float(PHASE_C);
            break;
        case 2:
            phase_p_pwm(PHASE_A, pwm_val);
            phase_n_pwm(PHASE_C, pwm_val);
            phase_float(PHASE_B);
            break;
        case 3:
            phase_p_pwm(PHASE_B, pwm_val);
            phase_n_pwm(PHASE_C, pwm_val);
            phase_float(PHASE_A);
            break;
        case 4:
            phase_p_pwm(PHASE_B, pwm_val);
            phase_n_pwm(PHASE_A, pwm_val);
            phase_float(PHASE_C);
            break;
        case 5:
            phase_p_pwm(PHASE_C, pwm_val);
            phase_n_pwm(PHASE_A, pwm_val);
            phase_float(PHASE_B);
            break;
        case 6:
            phase_p_pwm(PHASE_C, pwm_val);
            phase_n_pwm(PHASE_B, pwm_val);
            phase_float(PHASE_A);
            break;
        default:
            break;
    }
}

void motor_pwm_set_freewheeling(void)
{
    irq_primask_disable();
    motor_pwm_stop();
    irq_primask_enable();
}

void motor_pwm_set_break(void)
{
    irq_primask_disable();
    motor_pwm_brake();
    irq_primask_enable();
}

uint8_t back_pwm, break_motor=1;

void set_pwm_compare(uint32_t duty_cycle){
    //duty_cycle = duty_cycle < _pwm_mid ? _pwm_mid : duty_cycle;
    LL_TIM_OC_SetCompareCH1(TIM1, duty_cycle);
    LL_TIM_OC_SetCompareCH2(TIM1, duty_cycle);
    LL_TIM_OC_SetCompareCH3(TIM1, duty_cycle);
}

void comutate_start_motor(){
    motor_pwm_brake();
    LL_TIM_EnableIT_UPDATE(TIM14);
    LL_TIM_EnableCounter(TIM14);//comutation timer
}

void motor_pwm_set_pwm_val(uint32_t duty_cycle) {

      // uprintf("d:%d, min:%d, max:%d, p0:%d\n", duty_cycle, _pwm_min, _pwm_max, get_pwm_duty());
    if(motor.running == 0 && duty_cycle > (_pwm_min) && duty_cycle < _pwm_max){
        comutate_start_motor();//comitate başlat
        motor.running = 1;
    }
    if(motor.running){
        _pwm_duty = LOWPASS_ALP(_pwm_duty, duty_cycle, 0.4);
        //_pwm_duty = run_comutate(duty_cycle);
        //stoped
        if(_pwm_duty <= (_pwm_min+2)){
            //uprintf("stop\n");
            motor_pwm_set_freewheeling();
            LL_TIM_DisableCounter(TIM14);//comutate timer'ını sıfırla
            //set_comutate_freq(0);
            motor.running = 0;
            break_motor = 0;
            speed_pwm = _pwm_mid;//_pwm_max * (mosfet_thr / 1000);
            _comate_freq = 300;
        }
        //running
        else if(back_pwm !=_pwm_duty && TIM1->CNT % 20==0){//pid lazım
            uint16_t freq = (uint16_t)map(_pwm_duty, _pwm_min, _pwm_max, 1500, 40000);
            set_comutate_freq(freq);
            back_pwm = _pwm_duty;
            _comate_freq = freq;
        }

        //check_rpm_threshold();

        if(speed_pwm > 750){
            set_pwm_compare(speed_pwm);
            speed_pwm--;
        }

    }else if(break_motor){
        motor_pwm_set_break();
        break_motor = 0;
    }

    //test
    //uprintf("rpm_time:%d\n", speed_pwm);

}


/* TIMER LOOP INTERRUPT */
void comutate_timer_callback(){

    uint8_t current_state;
    //uint32_t com_time_us;
    if (_step == 1 || _step == 6){
       current_state = get_comutator_value(2);
    }
    if (_step == 3 || _step == 2){            //        in phase two or 5 read from phase A Pf1
        current_state = get_comutator_value(1);
    }
    if (_step == 5 || _step == 4){                         // phase B pf0
        current_state =  get_comutator_value(0);
    }

    if(_comate_freq < 3000 && !current_state){
       _step++;
    }else{
        /*if (forward == 1){
            step++;
            if (step > 6) {
                step = 1;
                desync_check = 1;
            }
            rising = step % 2;
        }else{
            step--;
            if (step < 1) {
                step = 6;
                desync_check = 1;
            }
            rising = !(step % 2);
        }*/

        if (rising){
            if (current_state){
                _step++;
                //rising = _step % 2;
            }/*else{
                bad_count++;
                if(bad_count > 2){
                bemfcounter = 0;
                }*/
        } else{
            if(!current_state){
                _step++;
            }/*else{
                bad_count++;
                if(bad_count > 2){
                bemfcounter = 0;
              }
            }*/
        }
    }

    if(_step>6){
        _step = 1;
        //set_pwm_compare(_pwm_duty / 2);

        uint32_t com_time_us = TIM17->CNT - back_com_time;
        if(com_time_us < 0)com_time_us += 0xFFFF;
        back_com_time =  TIM17->CNT;
        //com_time_us = com_time_us / 100;
        //rpm_t = com_time_us * 4  //bir dönüş için geçen süre
        //curreent duty

        //speed_pwm = pid_calculate(&currentPid, actual_time, com_time_us);

        /*if(actual_time - back_com_time > 0){
            speed_pwm = speed_pwm>_pwm_mid ? _pwm_mid : speed_pwm+1;
            set_pwm_compare(speed_pwm);//remove
        }else{
            speed_pwm = speed_pwm<50 ? 50 : speed_pwm-1;
            set_pwm_compare(speed_pwm);//remove
        }*/

        actual_time = com_time_us;

        /*if(_comate_freq > com_time_us){
            speed_pwm = speed_pwm > _pwm_mid ? _pwm_mid : speed_pwm+1;
            set_pwm_compare(speed_pwm);
        }else{
            if(speed_pwm > 300){
                set_pwm_compare(speed_pwm);
                speed_pwm--;
            }
        }*/

        ////set_timer_autoreload(TIM1, com_time_us);
    }

    if(backstep !=_step){
        motor_step(_step, _pwm_duty);
        backstep = _step;
    }
}

void timer_sinus_callback(){ }


/* AUDIO */
void motorTuneReady() {
    set_pwm_compare(100);
  motor_step(1, 100);
  TIM1->PSC = 70;
  LL_mDelay(150);
  TIM1->PSC = 50;
  LL_mDelay(150);
  TIM1->PSC = 40;
  LL_mDelay(150);
  TIM1->PSC = 0;
  motor_pwm_set_freewheeling();
}

void motorTuneInput(uint8_t motorStepDebug) {
    set_pwm_compare(100);
  motor_step(motorStepDebug, 20);
  TIM1->PSC = 75;
  LL_mDelay(100);
  TIM1->PSC = 50;
  LL_mDelay(100);

  TIM1->PSC = 0;
  motor_pwm_set_freewheeling();
}

uint16_t get_pwm_duty(){
    return _pwm_duty;
}
