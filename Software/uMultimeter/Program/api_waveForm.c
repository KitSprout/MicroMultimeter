/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "module_ssd1331.h"
#include "api_waveForm.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *pWaveForm )
{
  pWaveForm->Channel = 3;
  pWaveForm->WindowColor = WHITE;
  pWaveForm->BackColor = BLACK;
  pWaveForm->Data[0] = 0;
  pWaveForm->Data[1] = 0;
  pWaveForm->Data[2] = 0;
  pWaveForm->Scale[0] = 100;
  pWaveForm->Scale[1] = 100;
  pWaveForm->Scale[2] = 100;
  pWaveForm->PointColor[0] = RED;
  pWaveForm->PointColor[1] = GREEN;
  pWaveForm->PointColor[2] = BLUE;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormPrint( WaveForm_Struct *pWaveForm, uint8_t display )
{
  uint8_t i, j;
  uint8_t TempY[WaveChannelMax] = {0};
  uint8_t CoordiY[WaveChannelMax] = {0};

  static uint16_t WavePic[WaveChannelMax][WaveFormW] = {0};

  for(i = 0; i < pWaveForm->Channel; i++) {
    for(j = 0; j < WaveFormW - 1; j++)
      WavePic[i][j] = WavePic[i][j+1];
    TempY[i] = (uint8_t)(pWaveForm->Data[i] / pWaveForm->Scale[i]);
    CoordiY[i] = WaveFormH - TempY[i] - 1;
    if((CoordiY[i] > 0) && (CoordiY[i] < WaveFormH))
      WavePic[i][WaveFormW-1] = CoordiY[i];
  }
  if(display == ENABLE) {
    for(i = 0; i < WaveFormW - 1; i++) {
      for(j = 0; j < pWaveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX+i+1, WaveWindowY+WavePic[j][i], pWaveForm->BackColor);
      for(j = 0; j < pWaveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX+i, WaveWindowY+WavePic[j][i], pWaveForm->PointColor[j]);
    }
    for(j = 0; j < pWaveForm->Channel; j++)
      OLED_DrawPixel(WaveWindowX, WaveWindowY+WavePic[j][0], pWaveForm->BackColor);
    OLED_DrawLineX(WaveWindowX,             WaveWindowY,             WaveFormW,	pWaveForm->WindowColor);
    OLED_DrawLineX(WaveWindowX,             WaveWindowY+WaveFormH,   WaveFormW, pWaveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX,             WaveWindowY,             WaveFormH, pWaveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX+WaveFormW-1, WaveWindowY,             WaveFormH, pWaveForm->WindowColor);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
