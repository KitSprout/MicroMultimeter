/* #include "stm32f3_tim_pwm.h" */

#ifndef __STM32F3_TIM_PWM_H
#define __STM32F3_TIM_PWM_H

#include "stm32f30x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define TIMx                    TIM4
#define TIMx_CLK_ENABLE()       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE)
#define TIMx_CHANNEL            TIM_CHANNEL_2
#define TIMx_PWM_PERI           TIMx->PSC
#define TIMx_PWM_PULSE          TIMx->ARR
#define TIMx_PWM_DUTY           TIMx->CCR2

#define PWM_MIN 0
#define PWM_MED 500
#define PWM_MAX 1000
/*====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_Config( void );

void TIM_PWM_setDuty( uint16_t duty );
void TIM_PWM_setFreq( uint32_t freq );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
