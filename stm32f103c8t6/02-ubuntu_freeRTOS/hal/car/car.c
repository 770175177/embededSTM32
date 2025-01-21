#include <car.h>

void car_go_ahead(int duty)
{
    if (duty < 30) {
        tim4_pwm_set_duty(PWM4_CH1, 0);
	    tim4_pwm_set_duty(PWM4_CH4, 0);
    } else {
        tim4_pwm_set_duty(PWM4_CH1, duty+85);
	    tim4_pwm_set_duty(PWM4_CH4, duty+85);
    }
    
}

void car_go_back(int duty)
{
    if (duty < 100) {
        tim4_pwm_set_duty(PWM4_CH2, 0);
	    tim4_pwm_set_duty(PWM4_CH3, 0);
    } else {
        tim4_pwm_set_duty(PWM4_CH2, duty);
	    tim4_pwm_set_duty(PWM4_CH3, duty);
    }
}

void car_stand_control(int duty)
{
    if (duty < 0)
        car_go_ahead(-duty);
    else
        car_go_back(duty);
}
