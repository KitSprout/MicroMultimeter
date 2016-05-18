/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_adc.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define ADCx                    ADC1
#define ADCx_CLK_ENABLE()       RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
#define ADCx_DR_ADDRESS         ADC1_DR_ADDRESS

#define ADCxP_PIN               GPIO_Pin_3
#define ADCxP_GPIO_PORT         GPIOA
#define ADCxP_CHANNEL           ADC_Channel_4

#define ADCxN_PIN               GPIO_Pin_2
#define ADCxN_GPIO_PORT         GPIOA
#define ADCxN_CHANNEL           ADC_Channel_3

#define ADCx_DMA_CHANNEL        DMA1_Channel1
#define ADCx_DMA_CLK_ENABLE()   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

static __IO uint16_t ADC_DMA_ConvBuf[ADC_BUF_SIZE][ADC_BUF_CHENNAL] = {0};
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Config
**功能 : ADC Config
**輸入 : None
**輸出 : None
**使用 : ADC_Config();
**====================================================================================================*/
/*====================================================================================================*/
__IO uint16_t calibrationValue = 0;

void ADC_Config( void )
{
  DMA_InitTypeDef DMA_InitStruct;
  ADC_InitTypeDef ADC_InitStruct;
  ADC_CommonInitTypeDef ADC_CommonInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* ADC Clk *******************************************************************/
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);
  ADCx_CLK_ENABLE();
  ADCx_DMA_CLK_ENABLE();

  /* ADC Pin *******************************************************************/
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStruct.GPIO_Pin  = ADCxP_PIN;
  GPIO_Init(ADCxP_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin  = ADCxN_PIN;
  GPIO_Init(ADCxN_GPIO_PORT, &GPIO_InitStruct);

  /* ADC DMA *******************************************************************/
  DMA_DeInit(ADCx_DMA_CHANNEL);
  DMA_InitStruct.DMA_PeripheralBaseAddr = ADCx_DR_ADDRESS;
  DMA_InitStruct.DMA_MemoryBaseAddr     = (uint32_t)ADC_DMA_ConvBuf;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralSRC;
  DMA_InitStruct.DMA_BufferSize         = ADC_BUF_CHENNAL * ADC_BUF_SIZE;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_Medium;
  DMA_InitStruct.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(ADCx_DMA_CHANNEL, &DMA_InitStruct);
  DMA_Cmd(ADCx_DMA_CHANNEL, ENABLE);

  /* ADC Calibration ***********************************************************/
  ADC_VoltageRegulatorCmd(ADCx, ENABLE);
  delay_ms(10);

  ADC_SelectCalibrationMode(ADCx, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADCx);

  while(ADC_GetCalibrationStatus(ADCx) != RESET);
  calibrationValue = ADC_GetCalibrationValue(ADCx);

  /* ADC Common Init ***********************************************************/
  ADC_CommonInitStruct.ADC_Mode             = ADC_Mode_Interleave;             // ADC_Mode_Independent
  ADC_CommonInitStruct.ADC_Clock            = ADC_Clock_AsynClkMode;
  ADC_CommonInitStruct.ADC_DMAAccessMode    = ADC_DMAAccessMode_1;
  ADC_CommonInitStruct.ADC_DMAMode          = ADC_DMAMode_Circular;
  ADC_CommonInitStruct.ADC_TwoSamplingDelay = 0;
  ADC_CommonInit(ADCx, &ADC_CommonInitStruct);

  /* ADC Init *****************************************************************/
  ADC_InitStruct.ADC_ContinuousConvMode    = ADC_ContinuousConvMode_Enable;
  ADC_InitStruct.ADC_Resolution            = ADC_Resolution_12b; 
  ADC_InitStruct.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStruct.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStruct.ADC_DataAlign             = ADC_DataAlign_Right;
  ADC_InitStruct.ADC_OverrunMode           = ADC_OverrunMode_Disable;   
  ADC_InitStruct.ADC_AutoInjMode           = ADC_AutoInjec_Disable;  
  ADC_InitStruct.ADC_NbrOfRegChannel       = ADC_BUF_SIZE;
  ADC_Init(ADCx, &ADC_InitStruct);

  /* ADC Regular Config *******************************************************/
  ADC_RegularChannelConfig(ADCx, ADCxP_CHANNEL, 1, ADC_SampleTime_601Cycles5);
  ADC_RegularChannelConfig(ADCx, ADCxN_CHANNEL, 2, ADC_SampleTime_601Cycles5);

  /* Enable & Start ***********************************************************/
  ADC_DMACmd(ADCx, ENABLE);
  ADC_Cmd(ADCx, ENABLE);
  while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_RDY));
  DMA_Cmd(ADCx_DMA_CHANNEL, ENABLE);
  ADC_StartConversion(ADCx); 
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
