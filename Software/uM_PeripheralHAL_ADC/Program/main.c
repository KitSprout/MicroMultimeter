/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "drivers\stm32f3_adc.h"
#include "modules\module_ssd1331.h"

#include "uMultimeter.h"
/*====================================================================================================*/
/*====================================================================================================*/
void PROBE_OCH_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;

  GPIO_InitStruct.Pin   = GPIO_PIN_7;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  __GPIO_SET(GPIOB, GPIO_PIN_7);
}
void System_Init( void )
{
  UM_Init();
  PROBE_OCH_Config();
  ADC_Config();
}

int main( void )
{
  uint32_t adc_data = 0;

  System_Init();

  OLED_Clear(BLACK);

  while(1) {
    adc_data = ADC_getData(1);
    OLED_PutNum((OLED_W >> 1) - 6*2, OLED_H >> 1, Type_D, 4, adc_data, WHITE, BLACK);    // center
    delay_ms(100);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
