/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f3_system.h"
#include "stm32f3_dac.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define DACx                    DAC1
#define DACx_CLK_ENABLE()       RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

#define DACx1_PIN               GPIO_Pin_4
#define DACx1_GPIO_PORT         GPIOA
#define DACx1_CHANNEL           DAC_Channel_1
#define DACx1_DATA              DACx->DHR12R1

#define DACx2_PIN               GPIO_Pin_5
#define DACx2_GPIO_PORT         GPIOA
#define DACx2_CHANNEL           DAC_Channel_2
#define DACx2_DATA              DACx->DHR12R2
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC_Config
**功能 : DAC Config
**輸入 : None
**輸出 : None
**使用 : DAC_Config();
**====================================================================================================*/
/*====================================================================================================*/
void DAC_Config( void )
{
  DAC_InitTypeDef DAC_InitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;

  /* DAC Clk *******************************************************************/
  DACx_CLK_ENABLE();

  /* DAC Pin *******************************************************************/
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_InitStruct.GPIO_Pin  = DACx1_PIN;
  GPIO_Init(DACx1_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin  = DACx2_PIN;
  GPIO_Init(DACx1_GPIO_PORT, &GPIO_InitStruct);

  /* DAC Init *****************************************************************/
  DAC_DeInit(DACx); 
  DAC_InitStruct.DAC_Trigger        = DAC_Trigger_None;
  DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
  DAC_InitStruct.DAC_Buffer_Switch  = DAC_BufferSwitch_Disable;
  DAC_Init(DACx, DACx1_CHANNEL, &DAC_InitStruct);
  DAC_Init(DACx, DACx2_CHANNEL, &DAC_InitStruct);

  /* Enable & Start ***********************************************************/
  DAC_Cmd(DACx, DACx1_CHANNEL, ENABLE);
  DAC_Cmd(DACx, DACx2_CHANNEL, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : DAC_SetData
**功能 : Set DAC Data
**輸入 : None
**輸出 : None
**使用 : DAC_SetData(DAC_Channel_1, 1024);
**====================================================================================================*/
/*====================================================================================================*/
void DAC_SetData( uint8_t channel, uint16_t data )
{
  if(channel == DAC_Channel_1)
    DACx1_DATA = data;
  else if(channel == DAC_Channel_2)
    DACx2_DATA = data;
}
/*====================================================================================================*/
/*====================================================================================================*/
