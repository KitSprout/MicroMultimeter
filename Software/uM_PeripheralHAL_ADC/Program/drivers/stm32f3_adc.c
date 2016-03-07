/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_adc.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define ADCx                    ADC1
#define ADCx_CLK_ENABLE()       __HAL_RCC_ADC12_CLK_ENABLE()
#define ADCx_CHANNEL            ADC_CHANNEL_4
#define ADCx_IRQn               ADC1_2_IRQn

#define ADCx_DMA_CLK_ENABLE()   __HAL_RCC_DMA1_CLK_ENABLE()
#define ADCx_DMA_CHANNEL        DMA1_Channel1
#define ADCx_DMA_IRQn           DMA1_Channel1_IRQn

#define ADCx_GPIO_PIN           GPIO_PIN_3
#define ADCx_GPIO_PORT          GPIOA
#define ADCx_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

ADC_HandleTypeDef ADC_HandleStruct;

__IO uint16_t ADC_DMA_ConvBuf[ADC_BUF_SIZE][ADC_BUF_CHENNAL];
/*====================================================================================================*/
/*====================================================================================================*
**函數 : HAL_ADC_MspInit
**功能 : ADC Msp Init
**輸入 : hadc
**輸出 : None
**使用 : HAL_ADC_MspInit(&hadc);
**====================================================================================================*/
/*====================================================================================================*/
void HAL_ADC_MspInit( ADC_HandleTypeDef *hadc )
{
  static DMA_HandleTypeDef DMA_HandleStruct;

  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;

  /* Enable clock ******************************************************************/
  ADCx_CLK_ENABLE();
  ADCx_DMA_CLK_ENABLE();
  ADCx_GPIO_CLK_ENABLE();

  /* Enable asynchronous clock source of ADCx **************************************/
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_ADC12;
  RCC_PeriphCLKInitStruct.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV4;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

  /* Config GPIO ******************************************************************/
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Pin  = ADCx_GPIO_PIN;
  HAL_GPIO_Init(ADCx_GPIO_PORT, &GPIO_InitStruct);

//  GPIO_InitStruct.Pin  = ADCx_2_GPIO_PIN;
//  HAL_GPIO_Init(ADCx_2_GPIO_PORT, &GPIO_InitStruct);

  /* Config DMA *****************************************************************/
  DMA_HandleStruct.Instance                 = ADCx_DMA_CHANNEL;
  DMA_HandleStruct.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  DMA_HandleStruct.Init.PeriphInc           = DMA_PINC_DISABLE;
  DMA_HandleStruct.Init.MemInc              = DMA_MINC_ENABLE;
  DMA_HandleStruct.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  DMA_HandleStruct.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  DMA_HandleStruct.Init.Mode                = DMA_CIRCULAR;
  DMA_HandleStruct.Init.Priority            = DMA_PRIORITY_MEDIUM;
  HAL_DMA_DeInit(&DMA_HandleStruct);
  HAL_DMA_Init(&DMA_HandleStruct);

  __HAL_LINKDMA(hadc, DMA_Handle, DMA_HandleStruct);

  /* Config NVIC *****************************************************************/
  // DMA interrupt - Priority: high-priority
  HAL_NVIC_SetPriority(ADCx_DMA_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(ADCx_DMA_IRQn);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Config
**功能 : ADC Config
**輸入 : hadc
**輸出 : None
**使用 : ADC_Config();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Config( void )
{
  ADC_ChannelConfTypeDef ADC_ChannelConfStruct;
  HAL_StatusTypeDef state;

  /* Config ADC *****************************************************************/
  ADC_HandleStruct.Instance = ADCx;
  ADC_HandleStruct.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV1;
  ADC_HandleStruct.Init.Resolution            = ADC_RESOLUTION_12B;
  ADC_HandleStruct.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  ADC_HandleStruct.Init.ScanConvMode          = ENABLE;
  ADC_HandleStruct.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  ADC_HandleStruct.Init.LowPowerAutoWait      = DISABLE;
  ADC_HandleStruct.Init.ContinuousConvMode    = ENABLE;
  ADC_HandleStruct.Init.NbrOfConversion       = ADC_BUF_CHENNAL;
  ADC_HandleStruct.Init.DiscontinuousConvMode = ENABLE;
  ADC_HandleStruct.Init.NbrOfDiscConversion   = 1;
  ADC_HandleStruct.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
  ADC_HandleStruct.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  ADC_HandleStruct.Init.DMAContinuousRequests = ENABLE;
  ADC_HandleStruct.Init.Overrun               = ADC_OVR_DATA_OVERWRITTEN;
  HAL_ADC_DeInit(&ADC_HandleStruct);
  state = HAL_ADC_Init(&ADC_HandleStruct);
  if(state != HAL_OK)
    while(1) { ; }

  /* Config ADC Chennal **********************************************************/
  ADC_ChannelConfStruct.SamplingTime = ADC_SAMPLETIME_601CYCLES_5;
  ADC_ChannelConfStruct.SingleDiff   = ADC_SINGLE_ENDED;
  ADC_ChannelConfStruct.OffsetNumber = ADC_OFFSET_NONE;
  ADC_ChannelConfStruct.Offset       = 0;

  // ADC1_CH1 Channel
  ADC_ChannelConfStruct.Channel = ADCx_CHANNEL;
  ADC_ChannelConfStruct.Rank    = ADC_REGULAR_RANK_1;
  state = HAL_ADC_ConfigChannel(&ADC_HandleStruct, &ADC_ChannelConfStruct);
  if(state != HAL_OK)
    while(1) { ; }

  // ADC1_CH2 Channel
//  ADC_ChannelConfStruct.Channel = ADCx_2_CHANNEL;
//  ADC_ChannelConfStruct.Rank    = ADC_REGULAR_RANK_2;
//  state = HAL_ADC_ConfigChannel(&ADC_HandleStruct, &ADC_ChannelConfStruct);
//  if(state != HAL_OK)
//    while(1) { ; }

  /* Setup ADC *******************************************************************/
  state = HAL_ADCEx_Calibration_Start(&ADC_HandleStruct, ADC_SINGLE_ENDED);
  if(state != HAL_OK)
    while(1) { ; }
  state = HAL_ADC_Start_DMA(&ADC_HandleStruct, (uint32_t *)ADC_DMA_ConvBuf, ADC_BUF_SIZE * ADC_BUF_CHENNAL);
  if(state != HAL_OK)
    while(1) { ; }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_getData
**功能 : Get ADC Data
**輸入 : channel
**輸出 : None
**使用 : ADC_ConvVal = ADC_getData();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t ADC_getData( uint8_t channel )
{
  return (channel != 0) ? ADC_DMA_ConvBuf[0][channel - 1] : 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_getAverage
**功能 : Get Average
**輸入 : *pADC_data, adcSample
**輸出 : None
**使用 : ADC_getAverage(ADC_ConvVal, 64);
**====================================================================================================*/
/*====================================================================================================*/
void ADC_getAverage( uint16_t *pADC_data, uint8_t adcSample )
{
  uint32_t tmpData = 0;

  for(uint8_t i = 0; i < ADC_BUF_CHENNAL; i++) {
    tmpData = 0;
    for(uint8_t j = ADC_BUF_SIZE - adcSample; j < ADC_BUF_SIZE; j++)
      tmpData += ADC_DMA_ConvBuf[j][i];
    pADC_data[i] = (uint16_t)(tmpData / adcSample);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
