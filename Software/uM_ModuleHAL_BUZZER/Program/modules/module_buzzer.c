/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "module_buzzer.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define BUZZER_GPIO_PIN           GPIO_PIN_15
#define BUZZER_GPIO_PORT          GPIOB
#define BUZZER_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUZZER_GPIO_AF            GPIO_AF1_TIM15

#define BUZZER_TIMx               TIM15
#define BUZZER_TIMx_CLK_ENABLE()  __HAL_RCC_TIM15_CLK_ENABLE()
#define BUZZER_TIMx_CHANNEL       TIM_CHANNEL_2
#define BUZZER_TIMx_PWM_FREQ      BUZZER_TIMx->ARR
#define BUZZER_TIMx_PWM_DUTY      BUZZER_TIMx->CCR2
/*====================================================================================================*/
/*====================================================================================================*/
static __IO uint8_t  beepCmd      = DISABLE;
static __IO uint16_t beepLoudness = BUZZER_ON;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_Config
**功能 : Buzzer Config
**輸入 : None
**輸出 : None
**使用 : Buzzer_Config();
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_HandleTypeDef TIM_InitStruct;
  TIM_OC_InitTypeDef TIM_OC_InitStruct;

  /* Enable clock ******************************************************************/
  BUZZER_GPIO_CLK_ENABLE();
  BUZZER_TIMx_CLK_ENABLE();

  /* Config GPIO ******************************************************************/
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Alternate = BUZZER_GPIO_AF;
  GPIO_InitStruct.Pin       = BUZZER_GPIO_PIN;
  HAL_GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);

  /* Config TIM *****************************************************************/
  TIM_InitStruct.Instance               = BUZZER_TIMx;
  TIM_InitStruct.Init.Prescaler         = (uint32_t)(SystemCoreClock / 1000000) - 1;  // fclk = 1 MHz
  TIM_InitStruct.Init.Period            = BUZZER_MAX - 1;   // freq = 1 kHz
  TIM_InitStruct.Init.ClockDivision     = 0;
  TIM_InitStruct.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_InitStruct.Init.RepetitionCounter = 0;
  HAL_TIM_PWM_Init(&TIM_InitStruct);

  /* Config PWM Chennal *********************************************************/
  TIM_OC_InitStruct.OCMode       = TIM_OCMODE_PWM1;
  TIM_OC_InitStruct.OCFastMode   = TIM_OCFAST_DISABLE;
  TIM_OC_InitStruct.OCPolarity   = TIM_OCPOLARITY_HIGH;
  TIM_OC_InitStruct.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
  TIM_OC_InitStruct.OCIdleState  = TIM_OCIDLESTATE_RESET;
  TIM_OC_InitStruct.OCNIdleState = TIM_OCNIDLESTATE_RESET;

  TIM_OC_InitStruct.Pulse        = BUZZER_OFF;  // buzzer off
  HAL_TIM_PWM_ConfigChannel(&TIM_InitStruct, &TIM_OC_InitStruct, BUZZER_TIMx_CHANNEL);

  /* Setup PWM *******************************************************************/
  HAL_TIM_PWM_Start(&TIM_InitStruct, BUZZER_TIMx_CHANNEL);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_cmd
**功能 : Buzzer ENABLE/DISABLE
**輸入 : readData, threshold
**輸出 : None
**使用 : Buzzer_cmp(readData, threshold);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_cmd( uint8_t cmd )
{
  beepCmd = cmd;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_setLoudness
**功能 : Set Loudness
**輸入 : loudness (0 < loudness < 100)
**輸出 : None
**使用 : Buzzer_setLoudness(100);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_setLoudness( uint8_t loudness )
{
  beepLoudness = (loudness >= 100) ? BUZZER_ON : BUZZER_ON * (loudness * 0.01f);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_beep
**功能 : Buzzer Beep
**輸入 : loudness
**輸出 : None
**使用 : Buzzer_beep(loudness);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_beep( uint8_t loudness )
{
  Buzzer_setLoudness(loudness);
  BUZZER_TIMx_PWM_DUTY = beepLoudness;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_comp
**功能 : Buzzer Compare
**輸入 : readData, threshold
**輸出 : None
**使用 : Buzzer_comp(readData, threshold);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_comp( uint16_t readData, uint16_t threshold )
{
  if((beepCmd == DISABLE) || (readData > threshold))
    BUZZER_TIMx_PWM_DUTY = BUZZER_OFF;
  else
    BUZZER_TIMx_PWM_DUTY = beepLoudness;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_test
**功能 : Buzzer test
**輸入 : None
**輸出 : None
**使用 : Buzzer_test();
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_test( void )
{
  while(1) {
    Buzzer_beep(70);
    delay_ms(80);
    Buzzer_beep(0);
    delay_ms(80);
    Buzzer_beep(70);
    delay_ms(80);
    Buzzer_beep(0);
    delay_ms(1000);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
