/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "drivers\stm32f3_adc.h"
#include "modules\module_ssd1331.h"

#include "uMultimeter_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void UM_GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* Enable all GPIO Clk *******************************************************/
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  /* GPIO all analog input *****************************************************/
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_All & (~(GPIO_Pin_13 | GPIO_Pin_14));
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* GPIO Pin ******************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin   = LED_R_PIN;
  GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = LED_G_PIN;
  GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = LED_B_PIN;
  GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;

  GPIO_InitStruct.GPIO_Pin   = KEY_U_PIN;
  GPIO_Init(KEY_U_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = KEY_D_PIN;
  GPIO_Init(KEY_D_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = KEY_R_PIN;
  GPIO_Init(KEY_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = KEY_P_PIN;
  GPIO_Init(KEY_P_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = KEY_L_PIN;
  GPIO_Init(KEY_L_GPIO_PORT, &GPIO_InitStruct);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
void UM_ADC_Config( void )
{
  ADC_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void UM_SSD1331_Config( void )
{
  SSD1331_Config();
  delay_ms(100);
  SSD1331_Init();
  OLED_TestColoBar();
}
/*====================================================================================================*/
/*====================================================================================================*/
