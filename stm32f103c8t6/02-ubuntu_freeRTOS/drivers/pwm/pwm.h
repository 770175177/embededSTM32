#ifndef __PWM_H__
#define __PWM_H__
#include "sys.h"
#include "stm32f10x_tim.h"

/* GPIOB */
#define PWM4_CH1_PIN        GPIO_Pin_6
#define PWM4_CH2_PIN        GPIO_Pin_7
#define PWM4_CH3_PIN        GPIO_Pin_8
#define PWM4_CH4_PIN        GPIO_Pin_9

// 默认2分频，pwm频率 = 72000k / 2 / (899 + 1) = 40KHz
#define PWM4_40kHz_PER_MAX  (900 - 1)
#define PWM4_PER_MAX        PWM4_40kHz_PER_MAX

typedef enum _PWM4_CHANNEL {
    PWM4_CH1,
    PWM4_CH2,
    PWM4_CH3,
    PWM4_CH4,
} PWM4_CHANNEL;

void tim4_pwm_init(u16 period);
void tim4_pwm_set_duty(PWM4_CHANNEL ch, u16 duty);

#endif /* end __PWM_H__ */
