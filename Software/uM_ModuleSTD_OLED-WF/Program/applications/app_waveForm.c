/*=====================================================================================================*/
/*=====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "modules\module_ssd1331.h"

#include "app_waveForm.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *pWaveForm )
{
  for(uint16_t i = 0; i < pWaveForm->Channel; i++)
    pWaveForm->Data[i] = 0;
  for(uint16_t i = 0; i < WaveFormW; i++)
    WaveFormPrint(pWaveForm, DISABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormPrint( WaveForm_Struct *pWaveForm, uint8_t display )
{
  int16_t tmpY[WaveChannelMax] = {0};
  int16_t posY[WaveChannelMax] = {0};

  static uint16_t WavePic[WaveChannelMax][WaveFormW] = {0};

  /* update position */
  for(int16_t i = 0; i < pWaveForm->Channel; i++) {
    for(int16_t j = 0; j < WaveFormW - 1; j++)
      WavePic[i][j] = WavePic[i][j + 1];
    tmpY[i] = (int16_t)((float)pWaveForm->Data[i] / pWaveForm->Scale[i]);
    posY[i] = WaveFormH - tmpY[i];
    if((posY[i] > 0) && (posY[i] < WaveForm2H))
      WavePic[i][WaveFormW - 1] = posY[i];
  }
  if(display == ENABLE) {
    /* display */
    for(int16_t i = 0; i < WaveFormW - 1; i++) {
      /* clean old data */
      for(int16_t j = 0; j < pWaveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX + i + 1, WaveWindowY + WavePic[j][i], pWaveForm->BackColor);
//      /* plot line */
//      if((i % 10) < 3) {
//        for(int16_t j = 0; j <= pWaveFormH; j += (pWaveFormH / 10)) {
//          OLED_DrawPixel(WaveWindowX + i, WaveWindowY + pWaveFormH + j, pWaveForm->WindowColor);
//          OLED_DrawPixel(WaveWindowX + i, WaveWindowY + pWaveFormH - j, pWaveForm->WindowColor);
//        }
//      }
//      /* plot mid line */
//      OLED_DrawPixel(WaveWindowX + i, WaveWindowY + pWaveFormH, pWaveForm->WindowColor);
      /* display new data */
      for(int16_t j = 0; j < pWaveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX + i, WaveWindowY + WavePic[j][i], pWaveForm->PointColor[j]);
    }
    for(int16_t j = 0; j < pWaveForm->Channel; j++)
      OLED_DrawPixel(WaveWindowX, WaveWindowY + WavePic[j][0], pWaveForm->BackColor);
    /* plot window line */
    OLED_DrawLineX(WaveWindowX,                 WaveWindowY,                  WaveFormW,  pWaveForm->WindowColor);
    OLED_DrawLineX(WaveWindowX,                 WaveWindowY + WaveForm2H - 1, WaveFormW,  pWaveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX,                 WaveWindowY,                  WaveForm2H, pWaveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX + WaveFormW - 1, WaveWindowY,                  WaveForm2H, pWaveForm->WindowColor);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
