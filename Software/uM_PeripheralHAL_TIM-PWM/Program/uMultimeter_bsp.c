/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"

#include "uMultimeter.h"
#include "uMultimeter_bsp.h"
/*====================================================================================================*/
/*====================================================================================================*/
void UM_BSP_GPIO_Init( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk ******************************************************************/
  LED_R_GPIO_CLK_ENABLE();
  LED_G_GPIO_CLK_ENABLE();
  LED_B_GPIO_CLK_ENABLE();
  KEY_U_GPIO_CLK_ENABLE();
  KEY_D_GPIO_CLK_ENABLE();
  KEY_R_GPIO_CLK_ENABLE();
  KEY_P_GPIO_CLK_ENABLE();
  KEY_L_GPIO_CLK_ENABLE();

  /* GPIO Pin ******************************************************************/
  /* LED */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = LED_R_PIN;
  HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LED_G_PIN;
  HAL_GPIO_Init(LED_G_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = LED_B_PIN;
  HAL_GPIO_Init(LED_B_GPIO_PORT, &GPIO_InitStruct);

  /* KEY */
  GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

  GPIO_InitStruct.Pin   = KEY_U_PIN;
  HAL_GPIO_Init(KEY_U_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = KEY_D_PIN;
  HAL_GPIO_Init(KEY_D_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = KEY_R_PIN;
  HAL_GPIO_Init(KEY_R_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = KEY_P_PIN;
  HAL_GPIO_Init(KEY_P_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.Pin   = KEY_L_PIN;
  HAL_GPIO_Init(KEY_L_GPIO_PORT, &GPIO_InitStruct);

  LED_R_Set();
  LED_G_Set();
  LED_B_Set();
}
/*====================================================================================================*/
/*====================================================================================================*/
