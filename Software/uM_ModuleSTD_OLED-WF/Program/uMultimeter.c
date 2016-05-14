/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "modules\module_ssd1331.h"
#include "algorithms\algorithm_mathUnit.h"
#include "applications\app_waveForm.h"

#include "uMultimeter.h"
/*====================================================================================================*/
/*====================================================================================================*/
WaveForm_Struct WaveForm;
/*====================================================================================================*/
/*====================================================================================================*/
void UM_Init( void )
{
  SystemInit();
  HAL_InitTick();

  UM_GPIO_Config();
  UM_SSD1331_Config();
}
/*====================================================================================================*/
/*====================================================================================================*/
void WaveForm_demo( void )
{
  float data = 0.0f;
  static float rad = 0.0f;

  rad += 0.05f;
  for(uint8_t i = 1; i < 10; i = i + 2)
    data += (1.0f / i) * sinf(i * rad);

  WaveForm.Data[0] = sinf(rad) * 3000;
  WaveForm.Data[1] = data * 3000;
  WaveFormPrint(&WaveForm, ENABLE);
}

void UM_Loop( void )
{
	WaveForm.Channel       = 2;
	WaveForm.WindowColor   = WHITE;
	WaveForm.BackColor     = BLACK;
	WaveForm.Scale[0]      = 100;
	WaveForm.Scale[1]      = 100;
	WaveForm.PointColor[0] = GREEN;
	WaveForm.PointColor[1] = BLUE;
  WaveFormInit(&WaveForm);
  OLED_Clear(BLACK);

  while(1) {
    WaveForm_demo();
    LED_R_Toggle();
    LED_G_Toggle();
    LED_B_Toggle();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
