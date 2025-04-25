#include <car.h>

#define RIGHT_WHEEL_ADD     100
#define DOUBLE_WHEEL_ADD    250
#define LEFT_DUTY_SET(_x)   ((_x) + DOUBLE_WHEEL_ADD)
#define RIGHT_DUTY_SET(_x)  ((_x) + DOUBLE_WHEEL_ADD + RIGHT_WHEEL_ADD)

void car_go_back(int duty)
{
    l298n_set_state(L298N_IN1_PIN | L298N_IN4_PIN, L298N_DISABLE);
    l298n_set_state(L298N_IN2_PIN | L298N_IN3_PIN, L298N_ENABLE);

    tim4_pwm_set_duty(PWM4_CH1, LEFT_DUTY_SET(duty));  // left
    tim4_pwm_set_duty(PWM4_CH2, RIGHT_DUTY_SET(duty));     // right
}

void car_go_ahead(int duty)
{
    l298n_set_state(L298N_IN1_PIN | L298N_IN4_PIN, L298N_ENABLE);
    l298n_set_state(L298N_IN2_PIN | L298N_IN3_PIN, L298N_DISABLE);

    tim4_pwm_set_duty(PWM4_CH1, LEFT_DUTY_SET(duty));
    tim4_pwm_set_duty(PWM4_CH2, RIGHT_DUTY_SET(duty));
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
        car_go_ahead(-duty);
    else if (duty > 0)
        car_go_back(duty);
    else
        car_stop();
}
