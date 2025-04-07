#ifndef __PWM_H__
#define __PWM_H__
#include "sys.h"
#include "stm32f10x_tim.h"

/* GPIOB PWM */
#define PWM4_CH1_PIN        GPIO_Pin_6
#define PWM4_CH2_PIN        GPIO_Pin_7

/* GPIOB L298N */
#define L298N_IN1_PIN       GPIO_Pin_12
#define L298N_IN2_PIN       GPIO_Pin_13
#define L298N_IN3_PIN       GPIO_Pin_14
#define L298N_IN4_PIN       GPIO_Pin_15

// 默认2分频，pwm频率 = 72000k / 2 / (899 + 1) = 40KHz
#define PWM4_40kHz_PER_MAX  (900 - 1)
#define PWM4_PER_MAX        PWM4_40kHz_PER_MAX

typedef enum _PWM4_CHANNEL {
    PWM4_CH1,
    PWM4_CH2,
} PWM4_CHANNEL;

typedef enum _L298N_STATUS {
    L298N_DISABLE = 0,
    L298N_ENABLE = 1,
} L298N_STATUS;

void tim4_pwm_init(u16 period);
void tim4_pwm_set_duty(PWM4_CHANNEL ch, u16 duty);
void l298n_set_state(uint16_t gpio, L298N_STATUS stat);

#endif /* end __PWM_H__ */
