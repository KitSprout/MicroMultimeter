/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "uMultimeter_measure.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define TIM_CORE_FREQ               72000000

// OCH1 - PB0, TIM3 CH3
#define PROBE_OCH1_GPIO_PIN         GPIO_Pin_0
#define PROBE_OCH1_GPIO_PORT        GPIOB
#define PROBE_OCH1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define PROBE_OCH1_TIMx             TIM3
#define PROBE_OCH1_TIMx_CLK         RCC_APB1Periph_TIM3
#define PROBE_OCH1_TIMx_PERIOD      1000
#define PROBE_OCH1_TIMx_PRESCALER   144
#define PROBE_OCH1_DIV              PROBE_OCH1_TIMx->PSC
#define PROBE_OCH1_PERI             PROBE_OCH1_TIMx->ARR
#define PROBE_OCH1_DUTY             PROBE_OCH1_TIMx->CCR3
#define PROBE_OCH1_Set              _GPIO_SET(PROBE_OCH1_GPIO_PORT, PROBE_OCH1_GPIO_PIN)
#define PROBE_OCH1_Reset            _GPIO_RST(PROBE_OCH1_GPIO_PORT, PROBE_OCH1_GPIO_PIN)
#define PROBE_OCH1_Toggle           _GPIO_TOG(PROBE_OCH1_GPIO_PORT, PROBE_OCH1_GPIO_PIN)

// OCH2 - PA6, TIM3 CH1
#define PROBE_OCH2_GPIO_PIN         GPIO_Pin_6
#define PROBE_OCH2_GPIO_PORT        GPIOA
#define PROBE_OCH2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define PROBE_OCH2_Set              _GPIO_SET(PROBE_OCH2_GPIO_PORT, PROBE_OCH2_GPIO_PIN)
#define PROBE_OCH2_Reset            _GPIO_RST(PROBE_OCH2_GPIO_PORT, PROBE_OCH2_GPIO_PIN)
#define PROBE_OCH2_Toggle           _GPIO_TOG(PROBE_OCH2_GPIO_PORT, PROBE_OCH2_GPIO_PIN)

// ICH1 - PB1, TIM3 CH4, ADC12_9
#define PROBE_ICH1_GPIO_PIN         GPIO_Pin_1
#define PROBE_ICH1_GPIO_PORT        GPIOB
#define PROBE_ICH1_GPIO_CLK         RCC_APB2Periph_GPIOB
#define PROBE_ICH1_TIMx             TIM3
#define PROBE_ICH1_TIMx_CLK         RCC_APB1Periph_TIM3
#define PROBE_ICH1_TIMx_CH          TIM_Channel_4
#define PROBE_ICH1_TIMx_IT          TIM_IT_CC4
#define PROBE_ICH1_TIMx_PERIOD      2500
#define PROBE_ICH1_TIMx_PRESCALER   72
#define PROBE_ICH1_ADCx             ADC1
#define PROBE_ICH1_ADCx_CLK         RCC_APB2Periph_ADC1
#define PROBE_ICH1_ADCx_CH          ADC_Channel_9
#define PROBE_ICH1_ADCx_DR          ADC1_DR_ADDRESS
#define PROBE_ICH1_DMAx             DMA1_Channel1
#define PROBE_ICH1_DMAx_CLK         RCC_AHBPeriph_DMA1

// ICH2 - PA3, TIM2 CH4, ADC12_3
#define PROBE_ICH2_GPIO_PIN         GPIO_Pin_3
#define PROBE_ICH2_GPIO_PORT        GPIOA
#define PROBE_ICH2_GPIO_CLK         RCC_APB2Periph_GPIOA
#define PROBE_ICH2_ADCx             ADC1
#define PROBE_ICH2_ADCx_CLK         RCC_APB2Periph_ADC1
#define PROBE_ICH2_ADCx_CH          ADC_Channel_3
#define PROBE_ICH1_ADCx_DR          ADC1_DR_ADDRESS
#define PROBE_ICH2_DMAx             DMA1_Channel1
#define PROBE_ICH2_DMAx_CLK         RCC_AHBPeriph_DMA1

#define ADC_Channel   2
#define ADC_Sample    128
#define ADC_SampleDiv 7   // 128 = 2^7

#define PROBE_PWM_MAX  2500
#define PROBE_PWM_MED  1250
#define PROBE_PWM_MIN  0

#define PROBE_ON   PROBE_PWM_MIN
#define PROBE_OFF  PROBE_PWM_MAX
/*=====================================================================================================*/
/*=====================================================================================================*/
volatile uint16_t ProbeICH_ADC[ADC_Sample][ADC_Channel] = {0};
/*====================================================================================================*/
/*====================================================================================================*
**函數 : Probe_Config
**功能 : Probe Config
**輸入 : None
**輸出 : None
**使用 : Probe_Config();
**====================================================================================================*/
/*====================================================================================================*/
void Probe_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(PROBE_OCH1_TIMx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(PROBE_OCH1_GPIO_CLK | PROBE_OCH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

  ProbeICH_ADC_Config(ENABLE);

  /* PROBE_OCH1 */
  GPIO_InitStruct.GPIO_Pin = PROBE_OCH1_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(PROBE_OCH1_GPIO_PORT, &GPIO_InitStruct);
  /* PROBE_OCH2 */
  GPIO_InitStruct.GPIO_Pin = PROBE_OCH2_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(PROBE_OCH2_GPIO_PORT, &GPIO_InitStruct);

  /* OCH Time Base */
  TIM_TimeBaseStruct.TIM_Period = (uint16_t)(PROBE_OCH1_TIMx_PERIOD - 1);
  TIM_TimeBaseStruct.TIM_Prescaler = (uint16_t)(PROBE_OCH1_TIMx_PRESCALER - 1);
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(PROBE_OCH1_TIMx, &TIM_TimeBaseStruct);

  /************************** OCH PWM Output **************************************/
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = PROBE_OCH1_TIMx_PERIOD;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(PROBE_OCH1_TIMx, &TIM_OCInitStruct);

  TIM_OC3PreloadConfig(PROBE_OCH1_TIMx, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(PROBE_OCH1_TIMx, ENABLE);

  /* Setup */
  TIM_Cmd(PROBE_OCH1_TIMx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeICH_ADC_Config
**功能 : Probe ADC Input Channel Config
**輸入 : state
**輸出 : None
**使用 : ProbeICH_ADC_Config(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void ProbeICH_ADC_Config( FunctionalState state )
{
  DMA_InitTypeDef DMA_InitStruct;
  ADC_InitTypeDef ADC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* ADC Clk Init *************************************************************/
  RCC_AHBPeriphClockCmd(PROBE_ICH1_DMAx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(PROBE_ICH1_ADCx_CLK | PROBE_ICH2_ADCx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(PROBE_ICH1_GPIO_CLK | PROBE_ICH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* PROBE_ICH1 */
  GPIO_InitStruct.GPIO_Pin = PROBE_ICH1_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(PROBE_ICH1_GPIO_PORT, &GPIO_InitStruct);
  /* PROBE_ICH2 */
  GPIO_InitStruct.GPIO_Pin = PROBE_ICH2_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(PROBE_ICH2_GPIO_PORT, &GPIO_InitStruct);

  /* ADC DMA Channel Init ******************************************/
  DMA_DeInit(PROBE_ICH1_DMAx);
  DMA_InitStruct.DMA_PeripheralBaseAddr = PROBE_ICH1_ADCx_DR;                 // Peripheral address
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)&ProbeICH_ADC;                // Memory address
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                             // 內存作為數據傳輸的目的地
  DMA_InitStruct.DMA_BufferSize = ADC_Channel * ADC_Sample;                   // Memory Buffer Size
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;               // Peripheral address 遞增 Disable
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                        // Memory address 遞增 Enable
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;    // Peripheral Data Size 16bit
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;            // Memory Data Size 16bit
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;                                // 循環模式 Enable
  DMA_InitStruct.DMA_Priority = DMA_Priority_Medium;                          // ADC DMA通道 普通優先級
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;                                   // DMA通道x沒有設置為內存到內存傳輸
  DMA_Init(PROBE_ICH1_DMAx, &DMA_InitStruct);
  DMA_Cmd(PROBE_ICH1_DMAx, state);

  /* ADC Init *****************************************************************/
  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;                             // ADC1 和 ADC2 工作在獨立模式 
  ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                   // 掃描模式 
  ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                             // 連續轉換模式 
  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;            // 外部觸發 Disable
  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;                         // ADC數據右對齊
  ADC_InitStruct.ADC_NbrOfChannel = ADC_Channel;                              // 轉換ADC通道數目
  ADC_Init(PROBE_ICH1_ADCx, &ADC_InitStruct);

  /* ADC Regular Config *******************************************************/
  ADC_RegularChannelConfig(PROBE_ICH1_ADCx, PROBE_ICH1_ADCx_CH, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(PROBE_ICH2_ADCx, PROBE_ICH2_ADCx_CH, 2, ADC_SampleTime_239Cycles5);

  ADC_DMACmd(PROBE_ICH1_ADCx, state);
  ADC_Cmd(PROBE_ICH1_ADCx, state);
  if(state == ENABLE) {
    ADC_ResetCalibration(PROBE_ICH1_ADCx);
    while(ADC_GetResetCalibrationStatus(PROBE_ICH1_ADCx));
    ADC_StartCalibration(PROBE_ICH1_ADCx);
    while(ADC_GetCalibrationStatus(PROBE_ICH1_ADCx));
  }
  ADC_SoftwareStartConvCmd(PROBE_ICH1_ADCx, state);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeICH_PWM_Config
**功能 : ProbeICH PWM Input Channel Config
**輸入 : None
**輸出 : None
**使用 : ProbeICH_PWM_Config(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void ProbeICH_PWM_Config( FunctionalState state )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_ICInitTypeDef TIM_ICInitStruct;

  RCC_APB1PeriphClockCmd(PROBE_ICH1_TIMx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(PROBE_ICH1_GPIO_CLK | PROBE_ICH2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  TIM_DeInit(PROBE_ICH1_TIMx);

  /* PROBE_ICH1 */
  GPIO_InitStruct.GPIO_Pin = PROBE_ICH1_GPIO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(PROBE_ICH1_GPIO_PORT, &GPIO_InitStruct);

  /* OCH Time Base */
  TIM_TimeBaseStruct.TIM_Period = (uint16_t)(PROBE_OCH1_TIMx_PERIOD - 1);
  TIM_TimeBaseStruct.TIM_Prescaler = (uint16_t)(PROBE_OCH1_TIMx_PRESCALER - 1);
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(PROBE_OCH1_TIMx, &TIM_TimeBaseStruct);

  /************************** PWM Input **************************************/
  TIM_ICInitStruct.TIM_Channel = PROBE_ICH1_TIMx_CH;
  TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStruct.TIM_ICFilter = 0x0;
  TIM_PWMIConfig(PROBE_ICH1_TIMx, &TIM_ICInitStruct);

  TIM_SelectInputTrigger(PROBE_ICH1_TIMx, TIM_TS_TI2FP2);
  TIM_SelectSlaveMode(PROBE_ICH1_TIMx, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(PROBE_ICH1_TIMx, TIM_MasterSlaveMode_Enable);

  TIM_Cmd(PROBE_ICH1_TIMx, state);

  TIM_ITConfig(PROBE_ICH1_TIMx, PROBE_ICH1_TIMx_IT, state);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeOCH_OutputEN
**功能 : Output Enable / Disable
**輸入 : channel, state
**輸出 : None
**使用 : ProbeOCH_OutputEN(1, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void ProbeOCH_OutputEN( uint8_t channel, FunctionalState state )
{
  switch(channel) {
    case 0x00:
      PROBE_OCH1_DUTY = (state == ENABLE) ? PROBE_ON : PROBE_OFF;
      break;
    case 0x01:
      if(state == ENABLE)
        PROBE_OCH2_Reset;
      else
        PROBE_OCH2_Set;
      break;
    default:
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeOCH_SetDuty
**功能 : output enable / disable
**輸入 : channel, state
**輸出 : None
**使用 : ProbeOCH_SetDuty(4000); // 40% duty
**====================================================================================================*/
/*====================================================================================================*/
void ProbeOCH_SetDuty( uint16_t duty )
{
  duty = 10000 - duty;

  PROBE_OCH1_DUTY = (PROBE_OCH1_PERI + 1) * (duty / 10000.0f);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeOCH_SetFreq
**功能 : output enable / disable
**輸入 : channel, state
**輸出 : None
**使用 : ProbeOCH_SetFreq(500); // 500 Hz
**====================================================================================================*/
/*====================================================================================================*/
void ProbeOCH_SetFreq( uint32_t freq )
{
  uint32_t perFreq = 0;
  uint32_t tmpPeri = 0;

  perFreq = (TIM_CORE_FREQ / (PROBE_OCH1_DIV + 1));
  tmpPeri = perFreq / freq;
  if(99 < tmpPeri < 59999) {
    PROBE_OCH1_PERI = tmpPeri - 1;
    return;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeOCH_GetDuty
**功能 : Output Enable / Disable
**輸入 : None
**輸出 : duty
**使用 : duty = ProbeOCH_GetDuty();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t ProbeOCH_GetDuty( void )
{
  return (10000 - (PROBE_OCH1_DUTY * 10000.0f ) / (PROBE_OCH1_PERI + 1));
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeOCH_OutputEN
**功能 : Output Enable / Disable
**輸入 : channel, state
**輸出 : None
**使用 : ProbeOCH_OutputEN(1, ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
uint32_t ProbeOCH_GetFreq( void )
{
  uint32_t freq = TIM_CORE_FREQ / (PROBE_OCH1_DIV + 1);

  return (TIM_CORE_FREQ / (PROBE_OCH1_DIV + 1)) / (PROBE_OCH1_PERI + 1);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ProbeICH_ReadAveADC
**功能 : 將 ADC 轉換後的資料取平均
**輸入 : *pADC_Ave
**輸出 : None
**使用 : ADC_AveData = ProbeICH_ReadADC(0);
**====================================================================================================*/
/*====================================================================================================*/
#define MOVEAVE_LENGTH 4
uint16_t ProbeICH_ReadAveADC( uint8_t Channel )
{
  static uint16_t moveAve_Buf[2][MOVEAVE_LENGTH] = {0};
  const  uint16_t moveAve_Weighted[MOVEAVE_LENGTH] = {1, 2, 4, 9};  // sum = 16 = 2^4

  uint16_t tmpData = 0;
  uint32_t sumData = 0;

  for(uint16_t i = 0; i < ADC_Sample; i++)
    sumData += ProbeICH_ADC[i][Channel];
  tmpData = (sumData >> ADC_SampleDiv);

  sumData = 0;
  for(uint8_t i = 0; i < MOVEAVE_LENGTH-1; i++)
    moveAve_Buf[Channel][i] = moveAve_Buf[Channel][i+1];
  moveAve_Buf[Channel][MOVEAVE_LENGTH-1] = tmpData;
  for(uint8_t i = 0; i < MOVEAVE_LENGTH; i++)
    sumData += moveAve_Buf[Channel][i] * moveAve_Weighted[i];

  return (uint16_t)(sumData >> 4);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_measure_ADCtoVol
**功能 : 
**輸入 : adcData
**輸出 : None
**使用 : tmpData = uMultimeter_measure_ADCtoVol(readData);
**====================================================================================================*/
/*====================================================================================================*/
#define R1_Val    100000.0f // 100K
#define R2_Val    100000.0f // 100K
#define Vol_R1R2  1.611328125f // 0 ~ 6600 mV, ((3300 / 4096.0f) * ((R1_Val + R2_Val) / R2_Val))

uint16_t uMultimeter_measure_ADCtoVol( uint16_t adcData )
{
  return (uint16_t)(adcData * Vol_R1R2 + 0.5f);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_measure_ADCtoRes
**功能 : 
**輸入 : adcData
**輸出 : None
**使用 : tmpData = uMultimeter_measure_ADCtoRes(readData);
**====================================================================================================*/
/*====================================================================================================*/
uint32_t uMultimeter_measure_ADCtoRes( uint16_t adcData )
{
  return (uint32_t)(adcData * Vol_R1R2 + 0.5f);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
