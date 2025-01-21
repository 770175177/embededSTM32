#include <car.h>

void car_go_ahead(int duty)
{
    if (duty < 100) {
        tim4_pwm_set_duty(PWM4_CH1, 0);
	    tim4_pwm_set_duty(PWM4_CH4, 0);
    } else {
        tim4_pwm_set_duty(PWM4_CH1, duty + 100);
	    tim4_pwm_set_duty(PWM4_CH4, duty + 220);
    }
    
}

void car_go_back(int duty)
{
    if (duty < 100) {
        tim4_pwm_set_duty(PWM4_CH2, 0);
	    tim4_pwm_set_duty(PWM4_CH3, 0);
    } else {
        tim4_pwm_set_duty(PWM4_CH2, duty + 100);
	    tim4_pwm_set_duty(PWM4_CH3, duty + 220);
    }
}

void car_stand_control(int duty)
{
    if (duty < 0)
        car_go_ahead(-duty);
    if (duty > 0)
        car_go_back(duty);
}
