/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "module_buzzer.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define TIMx            TIM4
#define TIMx_CLK        RCC_APB1Periph_TIM4
#define TIMx_PERIOD     2500
#define TIMx_PRESCALER  20

#define TIMx_GPIO_PIN   GPIO_Pin_6
#define TIMx_GPIO_PORT  GPIOB
#define TIMx_GPIO_CLK   RCC_APB2Periph_GPIOB

#define BUZZER_FREQ     TIMx->ARR
#define BUZZER_DUTY     TIMx->CCR1

static uint16_t beepLoudness = BUZZER_ON;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_Config
**功能 : Buzzer 配置
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

  /* Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(TIMx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(TIMx_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* Buzzer GPIO */
  GPIO_InitStruct.GPIO_Pin = TIMx_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(TIMx_GPIO_PORT, &GPIO_InitStruct);

  /* Time Base */
  TIM_TimeBaseStruct.TIM_Period = (int16_t)(TIMx_PERIOD - 1);
  TIM_TimeBaseStruct.TIM_Prescaler = (int16_t)(TIMx_PRESCALER - 1);
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStruct);

  /************************** PWM Output **************************************/
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = BUZZER_MIN;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC1Init(TIMx, &TIM_OCInitStruct);
  TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIMx, ENABLE);

  /* Setup */
  TIM_Cmd(TIMx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_setLoudness
**功能 : 設定聲音大小
**輸入 : loudness, 0 < loudness < 100
**輸出 : None
**使用 : Buzzer_setLoudness(100);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_setLoudness( uint8_t loudness )
{
  beepLoudness = (loudness >= 100) ? BUZZER_MAX * 0.5f : BUZZER_MAX * loudness * 0.005f;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_cmp
**功能 : 若 readData 高於閥值 -> BUZZER_OFF，低於閥值 -> BUZZER_ON
**輸入 : readData, threshold
**輸出 : None
**使用 : Buzzer_cmp(readData, threshold);
**====================================================================================================*/
/*====================================================================================================*/
uint8_t Buzzer_cmp( uint16_t readData, uint16_t threshold )
{
  uint8_t state = readData <= threshold;

  BUZZER_DUTY = (state) ? beepLoudness : BUZZER_OFF;

  return state;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_cmp
**功能 : 若 readData 高於閥值 -> BUZZER_OFF，低於閥值 -> BUZZER_ON
**輸入 : readData, threshold
**輸出 : None
**使用 : Buzzer_cmp(readData, threshold);
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_cmd( FunctionalState state )
{
  BUZZER_DUTY = (state == ENABLE) ? BUZZER_ON : BUZZER_OFF;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Buzzer_test
**功能 : Buzzer 測試
**輸入 : None
**輸出 : None
**使用 : Buzzer_test();
**====================================================================================================*/
/*====================================================================================================*/
void Buzzer_test( void )
{
  uint8_t loudness = 70;

  while(1) {
    Buzzer_setLoudness(loudness);
    Delay_10ms(8);
    Buzzer_setLoudness(0);
    Delay_10ms(8);
    Buzzer_setLoudness(loudness);
    Delay_10ms(8);
    Buzzer_setLoudness(0);
    Delay_100ms(10);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
