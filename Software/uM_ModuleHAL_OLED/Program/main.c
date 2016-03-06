/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "modules\module_ssd1331.h"

#include "uMultimeter.h"
/*====================================================================================================*/
/*====================================================================================================*/
TIM_HandleTypeDef TIM_HandleStruct;
__IO uint32_t fps_count = 0;

uint32_t OLED_fpsTest( void )
{
  __IO uint32_t fps = 0;

  __HAL_RCC_TIM3_CLK_ENABLE();

  HAL_NVIC_SetPriority(TIM3_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);

  /* TIM Base Init */
  TIM_HandleStruct.Instance               = TIM3;
  TIM_HandleStruct.Init.Prescaler         = (uint32_t)(72); // 1MHz
  TIM_HandleStruct.Init.Period            = 1000 - 1;       // 1ms
  TIM_HandleStruct.Init.ClockDivision     = 0;
  TIM_HandleStruct.Init.CounterMode       = TIM_COUNTERMODE_UP;
  TIM_HandleStruct.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&TIM_HandleStruct);
  HAL_TIM_Base_Start_IT(&TIM_HandleStruct);

  OLED_TestFPS();
  fps = fps_count;

  OLED_Clear(BLACK);

  return fps;
}
void OLED_fpsTest_UpdateEven_CallBack( TIM_HandleTypeDef *htim )
{
  fps_count++;
}
/*====================================================================================================*/
/*====================================================================================================*/
void System_Init( void )
{
  UM_Init();
}

int main( void )
{
  uint32_t fps16 = 0;

  System_Init();

  fps16 = OLED_fpsTest(); // 16 frames, ms

  OLED_PutNum((OLED_W >> 1) - 6*4, OLED_H >> 1, Type_D, 8, fps16, WHITE, BLACK);    // center

  while(1) {}
}
/*====================================================================================================*/
/*====================================================================================================*/
