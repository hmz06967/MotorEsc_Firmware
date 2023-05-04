#include "main.h"
#include "io.h"
#include "input.h"
#include "uart.h"
#include "pwm.h"
#include "adc.h"
#include "comutate.h"

extern pwm_signal_t signal;
extern pwm_config_t config;

//struct motor_adc_sample _sample;

int main(void){

    io_init();
    init_input();
    motor_pwm_init();
    init_comutator();
    //init_adc();

    status_led_on();

    uprintf("Motor Driver v2.0\n");
    uprintf("EEPROM load..\n");
    uprintf("min: %d, max: %d, ver: %d, prs: %lu\n", config.calibzero, config.calibmax, config.ver, config.prs);

    motorTuneReady();

    LL_mDelay(1500);

    while(1){

        adc_update_run();

#ifdef TEST_MODE
        signal.state = 1;
        signal.timout = 10;
        signal.armed = 1;
        signal.pwm = 1990;
#else
        capture_callback();
#endif
        if(signal.state == 4){
            motorTuneInput(1);
            signal.armed = 1;
            signal.state = 1;
        }
        else if(signal.armed){
            status_led_off();
            //uprintf("s:%d, min:%d, max:%d, p0:%ld p1: %d p2: %d\n", signal.state, config.calibzero, config.calibmax, signal.pwm,  get_pwm_duty(), signal.capture);
            motor_pwm_set_pwm_val(signal.pwm);
        }
        else if(signal.state == 0 && --signal.timout < 2){//sinyal yok sıfırla.
            NVIC_SystemReset();
        }
        else if(signal.state == 2){
            //calibre mode
            uprintf("signal calibrating.. %d %d\n", 75-config.calibleft, signal.capture);
        }


        //printf_adc();

    }

}
