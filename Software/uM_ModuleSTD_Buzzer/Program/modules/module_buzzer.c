/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"

#include "module_buzzer.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define BUZZER_TIMx               TIM15
#define BUZZER_TIMx_CLK_ENABLE()  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE)
#define BUZZER_TIMx_CHANNEL       TIM_CHANNEL_2
#define BUZZER_TIMx_PWM_FREQ      BUZZER_TIMx->ARR
#define BUZZER_TIMx_PWM_DUTY      BUZZER_TIMx->CCR2

#define BUZZER_GPIO_PIN           GPIO_Pin_15
#define BUZZER_GPIO_PORT          GPIOB
#define BUZZER_GPIO_AF            GPIO_AF_1
#define BUZZER_GPIO_SOURCE        GPIO_PinSource15
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
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* TIMX Clk ******************************************************************/
  BUZZER_TIMx_CLK_ENABLE();

  /* GPIO AF Config ************************************************************/
  GPIO_PinAFConfig(BUZZER_GPIO_PORT, BUZZER_GPIO_SOURCE, BUZZER_GPIO_AF);

  /* GPIO Config ***************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin   = BUZZER_GPIO_PIN;
  GPIO_Init(BUZZER_GPIO_PORT, &GPIO_InitStruct);

  /* TIM Base Config ************************************************************/
  TIM_TimeBaseStruct.TIM_Prescaler     = (uint32_t)(SystemCoreClock / 1000000) - 1;   // fclk = 1 MHz
  TIM_TimeBaseStruct.TIM_Period        = BUZZER_MAX - 1;    // freq = 1 kHz
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(BUZZER_TIMx, &TIM_TimeBaseStruct);

  /* TIM OC Config **************************************************************/
  TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1; 
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;

  TIM_OCInitStruct.TIM_Pulse       = BUZZER_OFF;
  TIM_OC2Init(BUZZER_TIMx, &TIM_OCInitStruct);

  /* TIM Enable *****************************************************************/
  TIM_Cmd(BUZZER_TIMx, ENABLE);
  TIM_CtrlPWMOutputs(BUZZER_TIMx, ENABLE);
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
  Buzzer_beep(70);
  delay_ms(80);
  Buzzer_beep(0);
  delay_ms(80);
  Buzzer_beep(70);
  delay_ms(80);
  Buzzer_beep(0);
  delay_ms(1000);
}
/*====================================================================================================*/
/*====================================================================================================*/
