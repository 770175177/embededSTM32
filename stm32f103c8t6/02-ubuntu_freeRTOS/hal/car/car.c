#include <car.h>

void car_go_ahead(int duty)
{
    tim4_pwm_set_duty(PWM4_CH1, duty);
	tim4_pwm_set_duty(PWM4_CH4, duty+120);
}

void car_go_back(int duty)
{
	tim4_pwm_set_duty(PWM4_CH2, duty);
	tim4_pwm_set_duty(PWM4_CH3, duty+120);
}

void car_stand_control(int duty)
{
    if (duty < 0)
        car_go_ahead(-duty+300);
    if (duty > 0)
        car_go_back(duty+300);
}
