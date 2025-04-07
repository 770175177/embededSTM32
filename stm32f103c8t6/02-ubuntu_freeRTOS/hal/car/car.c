#include <car.h>

void car_go_ahead(int duty)
{
    l298n_set_state(L298N_IN1_PIN | L298N_IN4_PIN, L298N_DISABLE);
    l298n_set_state(L298N_IN2_PIN | L298N_IN3_PIN, L298N_ENABLE);

    tim4_pwm_set_duty(PWM4_CH1, duty+85);
    tim4_pwm_set_duty(PWM4_CH2, duty);
}

void car_go_back(int duty)
{
    l298n_set_state(L298N_IN1_PIN | L298N_IN4_PIN, L298N_ENABLE);
    l298n_set_state(L298N_IN2_PIN | L298N_IN3_PIN, L298N_DISABLE);

    tim4_pwm_set_duty(PWM4_CH1, duty+85);
    tim4_pwm_set_duty(PWM4_CH2, duty);
}

void car_stop()
{
    l298n_set_state(L298N_IN1_PIN | L298N_IN4_PIN, L298N_ENABLE);
    l298n_set_state(L298N_IN2_PIN | L298N_IN3_PIN, L298N_ENABLE);

    tim4_pwm_set_duty(PWM4_CH1, PWM4_PER_MAX);
    tim4_pwm_set_duty(PWM4_CH2, PWM4_PER_MAX);
}

void car_stand_control(int duty)
{
    if (duty < 0)
        car_go_back(-duty);
    else if (duty > 0)
        car_go_ahead(duty);
    else
        car_stop();
}
