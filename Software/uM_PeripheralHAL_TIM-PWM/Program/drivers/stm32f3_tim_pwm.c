/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_tim_pwm.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define TIMx                    TIM4
#define TIMx_CLK_ENABLE()       __HAL_RCC_TIM4_CLK_ENABLE()
#define TIMx_CHANNEL            TIM_CHANNEL_2
#define TIMx_PWM_FREQ           TIMx->ARR
#define TIMx_PWM_DUTY           TIMx->CCR2

#define TIMx_GPIO_PIN           GPIO_PIN_7
#define TIMx_GPIO_PORT          GPIOB
#define TIMx_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define TIMx_GPIO_AF            GPIO_AF2_TIM4
/*====================================================================================================*/
/*====================================================================================================*
**函數 : HAL_TIM_PWM_MspInit
**功能 : TIM PWM Msp Init
**輸入 : htim
**輸出 : None
**使用 : HAL_TIM_PWM_MspInit(&htim);
**====================================================================================================*/
/*====================================================================================================*/
void HAL_TIM_PWM_MspInit( TIM_HandleTypeDef *htim )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable clock ******************************************************************/
  TIMx_CLK_ENABLE();
  TIMx_GPIO_CLK_ENABLE();

  /* Config GPIO ******************************************************************/
  GPIO_InitStruct.Mode  = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Alternate = TIMx_GPIO_AF;
  GPIO_InitStruct.Pin       = TIMx_GPIO_PIN;
  HAL_GPIO_Init(TIMx_GPIO_PORT, &GPIO_InitStruct);
}
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
  TIM_HandleTypeDef TIM_InitStruct;
  TIM_OC_InitTypeDef TIM_OC_InitStruct;

  /* Config TIM *****************************************************************/
  TIM_InitStruct.Instance               = TIMx;
  TIM_InitStruct.Init.Prescaler         = (uint32_t)(SystemCoreClock / 1000000) - 1;   // fclk = 1 MHz
  TIM_InitStruct.Init.Period            = PWM_MAX - 1;  // freq = 1 kHz
  TIM_InitStruct.Init.ClockDivision     = 0;
  TIM_InitStruct.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_InitStruct.Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(&TIM_InitStruct);

  /* Config PWM Chennal *********************************************************/
  TIM_OC_InitStruct.OCMode      = TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCFastMode  = TIM_OCFAST_DISABLE;
  TIM_OC_InitStruct.OCPolarity  = TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState = TIM_OCIDLESTATE_RESET;
  TIM_OC_InitStruct.OCNIdleState= TIM_OCNIDLESTATE_RESET;

  TIM_OC_InitStruct.Pulse = (TIMx_PWM_FREQ + 1) >> 1; // 50% duty
  HAL_TIM_PWM_ConfigChannel(&TIM_InitStruct, &TIM_OC_InitStruct, TIMx_CHANNEL);

  /* Setup PWM *******************************************************************/
  HAL_TIM_PWM_Start(&TIM_InitStruct, TIMx_CHANNEL);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : TIM_PWM_setDuty
**功能 : TIM PWM Set Duty
**輸入 : duty
**輸出 : None
**使用 : TIM_PWM_setDuty(duty);
**====================================================================================================*/
/*====================================================================================================*/
void TIM_PWM_setDuty( uint32_t duty )
{
  TIMx_PWM_DUTY = (duty > PWM_MAX) ? (PWM_MAX) : (duty);
}
/*====================================================================================================*/
/*====================================================================================================*/
