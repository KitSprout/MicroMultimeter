/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_tim_pwm.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define TIMx_GPIO_PIN           GPIO_Pin_7
#define TIMx_GPIO_PORT          GPIOB
#define TIMx_GPIO_AF            GPIO_AF_2
#define TIMx_GPIO_SOURCE        GPIO_PinSource7
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIM_PWM_Config
**功能 : TIM PWM Config
**輸入 : None
**輸出 : None
**使用 : TIM_PWM_Config();
**====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* TIMX Clk ******************************************************************/
  TIMx_CLK_ENABLE();

  /* GPIO AF Config ************************************************************/
  GPIO_PinAFConfig(TIMx_GPIO_PORT, TIMx_GPIO_SOURCE, TIMx_GPIO_AF);

  /* GPIO Config ***************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin   = TIMx_GPIO_PIN;
  GPIO_Init(TIMx_GPIO_PORT, &GPIO_InitStruct);

  /* TIM Base Config ************************************************************/
  TIM_TimeBaseStruct.TIM_Prescaler     = (uint32_t)(SystemCoreClock / 1000000) - 1;   // fclk = 1 MHz
  TIM_TimeBaseStruct.TIM_Period        = PWM_MAX - 1;       // freq = 1 kHz
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStruct);

  /* TIM OC Config **************************************************************/
  TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1; 
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_Low;

  TIM_OCInitStruct.TIM_Pulse       = PWM_MIN;
  TIM_OC2Init(TIMx, &TIM_OCInitStruct);

  /* TIM Enable *****************************************************************/
  TIM_Cmd(TIMx, ENABLE);
//  TIM_CtrlPWMOutputs(TIMx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIM_PWM_setDuty
**功能 : TIM PWM Set Duty
**輸入 : duty
**輸出 : None
**使用 : TIM_PWM_setDuty(duty); // 0 ~ 1000
**====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_setDuty( uint16_t duty )
{
  TIMx_PWM_DUTY = (duty > PWM_MAX) ? (PWM_MAX) : (duty);
}
/*====================================================================================================*/
/*====================================================================================================*/
