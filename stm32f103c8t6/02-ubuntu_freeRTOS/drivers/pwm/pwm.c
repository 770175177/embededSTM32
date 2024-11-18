#include "pwm.h"

static u16 period;

// arr: 自动重装值
// psc: 时钟分频数
void tim1_pwm_init(u16 arr, u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);	// 使能GPIO时钟
	                                                                     	

	// 引脚服用为输出功能，输出TIM1 CH1的 PWM 脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				// TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	period = arr;
	TIM_TimeBaseStructure.TIM_Period = arr;					// 设置自动重装值 80K
	TIM_TimeBaseStructure.TIM_Prescaler = psc;				// 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;			// 设置时钟分割: TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);			// 根据 IM_TimeBaseInitStruct 初始化 TIMx 时间基数
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;		// 选择定时器模式：TIM脉冲调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;						// 设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	// 输出极性：Low
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);				// 初始化TIM1

	TIM_CtrlPWMOutputs(TIM1, ENABLE);						// MOE使能
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);		// CH1预装载使能
	TIM_ARRPreloadConfig(TIM1, ENABLE);						// 使能TIM1在ARR上的预装载寄存器
	TIM_Cmd(TIM1, ENABLE);									// 使能TIM1
}

// 百分比: per: 0-period
void tim1_pwm_set_duty(u16 duty)
{
	u16 set_value = 0;
	u16	per_value = 0;

	if (duty > period)
		duty = period;

	TIM_SetCompare1(TIM1, duty);
}

