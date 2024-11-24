#include "pwm.h"

// arr: 自动重装值
// psc: 时钟分频数
void tim4_pwm_init(u16 period)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);	// 使能GPIO时钟                                                    	

	// 引脚服用为输出功能，输出TIM4 CH1/CH2/CH3/CH4的 PWM 脉冲波形
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			// 复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = PWM4_CH1_PIN;				// TIM_CH1
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PWM4_CH2_PIN;				// TIM_CH2
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PWM4_CH3_PIN;				// TIM_CH3
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = PWM4_CH4_PIN;				// TIM_CH4
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = period;					// 设置自动重装值 80K
	TIM_TimeBaseStructure.TIM_Prescaler = 0;				// 不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;			// 设置时钟分割: TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);			// 根据 IM_TimeBaseInitStruct 初始化 TIMx 时间基数
 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;		// 选择定时器模式：TIM脉冲调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; // 比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;						// 设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	  // 输出极性：Low
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);				// 初始化TIM1 CH1
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);				// 初始化TIM1 CH2
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);				// 初始化TIM1 CH3
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);				// 初始化TIM1 CH4

	TIM_CtrlPWMOutputs(TIM4, ENABLE);						// MOE使能
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);		// CH1预装载使能
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);		// CH2预装载使能
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);		// CH3预装载使能
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);		// CH4预装载使能
	TIM_ARRPreloadConfig(TIM4, ENABLE);						// 使能TIM1在ARR上的预装载寄存器
	TIM_Cmd(TIM4, ENABLE);									// 使能TIM1
}

// 百分比: per: 0 - PWM4_PER_MAX
void tim4_pwm_set_duty(PWM4_CHANNEL ch, u16 duty)
{
	if (duty > PWM4_PER_MAX)
		duty = PWM4_PER_MAX;

	switch (ch) {
		case PWM4_CH1:
			TIM_SetCompare1(TIM4, duty);
			break;
    	case PWM4_CH2:
			TIM_SetCompare2(TIM4, duty);
			break;
    	case PWM4_CH3:
			TIM_SetCompare3(TIM4, duty);
			break;
    	case PWM4_CH4:
			TIM_SetCompare4(TIM4, duty);
			break;
		default:
			break;
	}
}

