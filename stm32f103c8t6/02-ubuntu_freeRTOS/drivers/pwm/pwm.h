#ifndef __PWM_H__
#define __PWM_H__
#include "sys.h"
#include "stm32f10x_tim.h"

void tim1_pwm_init(u16 arr,u16 psc);
void tim1_pwm_set_duty(u16 duty);

#endif /* end __PWM_H__ */
