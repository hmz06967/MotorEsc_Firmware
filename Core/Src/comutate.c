#include "io.h"
#include "comutate.h"
#include "adc.h"
#include "pwm.h"

uint8_t  _step = 0;

uint8_t next_step;
/**
 *      @arg @ref LL_TIM_CHANNEL_CH1
  *         @arg @ref LL_TIM_CHANNEL_CH1N
  *         @arg @ref LL_TIM_CHANNEL_CH2
  *         @arg @ref LL_TIM_CHANNEL_CH2N
  *         @arg @ref LL_TIM_CHANNEL_CH3
  *         @arg @ref LL_TIM_CHANNEL_CH3N
  *         @arg @ref LL_TIM_CHANNEL_CH4
__STATIC_INLINE uint32_t LL_TIM_CC_IsEnabledChannel(TIM_TypeDef *TIMx, uint32_t Channels)
 */

void init_comutator(void){
    LL_TIM_EnableCounter(INTERVAL_TIM);
    LL_TIM_EnableCounter(TIM17);
}

#ifdef COMP
uint32_t pwm_val, pre_comp_time, __duty, get_time_dif;
int16_t pwm_back_time = 1;
uint8_t back_step;

int32_t comutator_val[10],
        comfalle[3],
        comrise[3];


uint8_t lpftime = 0;
uint8_t lpfaplha = 10;
int16_t timelaps;

uint32_t get_timer_diff(uint32_t *btime){
    return  0;//(INTERVAL_TIM->CNT > *btime ? (INTERVAL_TIM->CNT - *btime) : (*btime - INTERVAL_TIM->CNT));
}

uint8_t LPF_comp(uint8_t phase){
    /*for(uint8_t phase = 0; phase < 3; phase++){
        //if(!lpftime){
        comutator_val[phase+3] +=  get_comutator_value(phase);
        comutator_val[phase] = comutator_val[phase+3] > (lpfaplha/2);
        //}else{
        //}
    }
    lpftime = ((lpftime < lpfaplha) ? lpftime +1 : 0);*/

    //lpfaplha = get_timer_diff(&comutator_val[phase+6]);
   lpftime = comutator_val[phase+3];

   if(lpftime==0){
       lpftime = get_comutator_value(phase) && get_step_pwm()!=5;//ilk 1 olduğunda
       if(lpftime){
           comfalle[phase] = TIM17->CNT; // get_timer_diff (&comutator_val[phase]);
       }
   }else if(lpftime==1 && get_comutator_value(phase) == 0){
       lpftime  = 2;
   }else if(lpftime==2){//_1-_2-
        lpftime = 0;
        get_time_dif = (TIM17->CNT - comfalle[phase]); //get_timer_diff (&comutator_val[phase])/1000;
        if(get_time_dif < 0)get_time_dif += 0xFFFF;
        comutator_val[phase] = LOWPASS_ALP(get_time_dif, comutator_val[phase], 0.9);
    }

    comutator_val[phase+3] = lpftime;
    return (comutator_val[phase]);
}

uint32_t get_comp_value(uint8_t phase){
    return comutator_val[phase];
}

uint8_t t1=1;
void check_comperator(){
    /*LPF_comp(0);
    LPF_comp(1);
    LPF_comp(2);
    if(get_comutator_value(0)){
        _step = get_comutator_value(1) ? 6 : 5;
    }else if(get_comutator_value(1)){
        _step = get_comutator_value(2) ? 4 : 3;
    }else if(get_comutator_value(2)){
        _step = get_comutator_value(0) ? 2 : 1;
    }

    timelaps = comutator_val[7] - comutator_val[2];
    comutator_val[7] = comutator_val[2];

    //uprintf("step:%d\n", _step);
*/
    /*uint8_t t1 = 5*(comutator_val[0]>1000),
            t2 = 5*(comutator_val[1]>1000),
            t3 = 5*(comutator_val[2]>1000);*/

    //uprintf("A:%d\n", INTERVAL_TIM->CNT);

    if(get_comutator_value(t1)){

        //uprintf("Step:%d,Time:%d\n", _step, t1+4);
        if(_step< 3){
            t1 = 1;//5*get_comutator_value(1);
        } else if(_step>2||_step<5){
            t1 = 2;//5*get_comutator_value(2);
        }else if(_step>4||_step<7){
            t1 = 0;//5*get_comutator_value(2);
        }
        timelaps = INTERVAL_TIM->CNT;
        INTERVAL_TIM->CNT = 0;
    }
    //uprintf("A:%d,B:%d,C:%d\n", 5*get_comutator_value(0), 5*get_comutator_value(1)+6, 5*get_comutator_value(2)+12);
}

uint32_t get_pwm_us(){
    return 100000 / get_timer_pwm_freq();
}

uint32_t max_comptime;
uint32_t now_comptime;
uint32_t back_comptime;
uint16_t _duty = 1;
uint16_t run_comutate(uint16_t duty){

    //_step = get_step_pwm();

    //comrise[0] = LPF_comp(0);
    //comrise[1] = LPF_comp(1);
    //comrise[1] = LPF_comp(2);


    now_comptime = LPF_comp(0)*10; //(comrise[0] + comrise[0] + comrise[0]) / 3;
    uprintf("t1:%d,d:%d\n", now_comptime, duty);


    back_comptime = now_comptime;
    return duty;

    if(duty<200){
        _duty = duty;
    }
    else if(now_comptime <= max_comptime){
        max_comptime = now_comptime;
        if(_duty < duty){
            _duty++;
        }else{
            _duty = duty;
        }
    }else{
        if(_duty==1){
            _duty = duty;
        }
        else if(TIM17->CNT % 1000==0)
            _duty= _duty<200 ? _duty : _duty-10;
    }

    //mosfet sinüs sinyali oluştur
    /* if(chA_sin>165)chA_sin = 15;
    set_timer_autoreload(TIM1, calculate_pwm_sin(chA_sin));
    chA_sin++;

   //init interrrupt comutate
    //adc ile okuma yaparak comutate kullanacağız ok

    if(chA_sin>165)chA_sin = 15;
    if(chB_sin>165)chB_sin = 15;
    if(chC_sin>165)chC_sin = 15;

    if(chCN_sin>165)chCN_sin = 15;
    if(chCN_sin>165)chCN_sin = 15;
    if(chCN_sin>165)chCN_sin = 15;

    //_step = get_step_pwm();*

    if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH1)){
        pwm_val = calculate_pwm_sin(chA_sin);
        LL_TIM_OC_SetCompareCH1(TIM1, pwm_val);
        chA_sin++;
    }else if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH1N)){
        pwm_val = calculate_pwm_sin(chAN_sin);
        LL_TIM_OC_SetCompareCH1(TIM1, pwm_val);
        chAN_sin++;
    }

    if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH2)){
        pwm_val = calculate_pwm_sin(chB_sin);
        LL_TIM_OC_SetCompareCH2(TIM1, pwm_val);
        chB_sin++;
    }else if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH2N)){
        pwm_val = calculate_pwm_sin(chBN_sin);
        LL_TIM_OC_SetCompareCH2(TIM1, pwm_val);
        chBN_sin++;
    }

    if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH3)){
        pwm_val = calculate_pwm_sin(chC_sin);
        LL_TIM_OC_SetCompareCH3(TIM1, pwm_val);
        chC_sin++;
    }else if(LL_TIM_CC_IsEnabledChannel(TIM1, LL_TIM_CHANNEL_CH3N)){
        pwm_val = calculate_pwm_sin(chCN_sin);
        LL_TIM_OC_SetCompareCH3(TIM1, pwm_val);
        chCN_sin++;
    }

    */

    /**if(pwm_back_time > 0){
        if(back_step!=_step){
            INTERVAL_TIM->CNT = 0;
            back_step = _step;
        }
    } pwm_back_time = INTERVAL_TIM->CNT - (get_pwm_us()/3);
    */

    /*check_comperator();

    if(timelaps>0){
        if(duty < __duty){
            __duty = duty;
        }
        duty--;

    }else{
        if(duty > __duty){
            __duty++;
        }
    }*/

    //test

    /*
    //A+ B-
    if(get_comutator_value(2))GPIOB->BSRR = LL_GPIO_PIN_3;//ch3 a 1
    else GPIOB->BRR = LL_GPIO_PIN_3;

    //B+ C-
    if(get_comutator_value(1))GPIOB->BSRR = LL_GPIO_PIN_4;//ch2 b 3
    else GPIOB->BRR = LL_GPIO_PIN_4;

    //C+ A-
    if(get_comutator_value(0))GPIOB->BSRR = LL_GPIO_PIN_5;//ch1 c 5
    else GPIOB->BRR = LL_GPIO_PIN_5;
*/

    //uprintf("t1: %d, d: %d ,s:%d\n", comutator_val[2], __duty,_step);

    return _duty;

}

uint8_t get_step(void){
    if(_step>6 || _step<1){
        _step = 1;
    }
    return _step;
}
#endif
