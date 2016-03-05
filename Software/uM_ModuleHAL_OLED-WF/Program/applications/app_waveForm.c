/*=====================================================================================================*/
/*=====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "modules\module_ssd1331.h"

#include "app_waveForm.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *waveForm )
{
  waveForm->Channel       = 3;
  waveForm->WindowColor   = WHITE;
  waveForm->BackColor     = BLACK;
  waveForm->Data[0]       = 0;
  waveForm->Data[1]       = 0;
  waveForm->Scale[0]      = 100;
  waveForm->Scale[1]      = 100;
  waveForm->PointColor[0] = GREEN;
  waveForm->PointColor[1] = BLUE;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormPrint( WaveForm_Struct *waveForm, uint8_t display )
{
  int16_t tmpY[WaveChannelMax] = {0};
  int16_t posY[WaveChannelMax] = {0};

  static uint16_t WavePic[WaveChannelMax][WaveFormW] = {0};

  /* update position */
  for(int16_t i = 0; i < waveForm->Channel; i++) {
    for(int16_t j = 0; j < WaveFormW - 1; j++)
      WavePic[i][j] = WavePic[i][j + 1];
    tmpY[i] = (int16_t)((float)waveForm->Data[i] / waveForm->Scale[i]);
    posY[i] = WaveFormH - tmpY[i];
    if((posY[i] > 0) && (posY[i] < WaveForm2H))
      WavePic[i][WaveFormW - 1] = posY[i];
  }
  if(display == ENABLE) {
    /* display */
    for(int16_t i = 0; i < WaveFormW - 1; i++) {
      /* clean old data */
      for(int16_t j = 0; j < waveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX + i + 1, WaveWindowY + WavePic[j][i], waveForm->BackColor);
//      /* plot line */
//      if((i % 10) < 3) {
//        for(int16_t j = 0; j <= WaveFormH; j += (WaveFormH / 10)) {
//          OLED_DrawPixel(WaveWindowX + i, WaveWindowY + WaveFormH + j, waveForm->WindowColor);
//          OLED_DrawPixel(WaveWindowX + i, WaveWindowY + WaveFormH - j, waveForm->WindowColor);
//        }
//      }
//      /* plot mid line */
//      OLED_DrawPixel(WaveWindowX + i, WaveWindowY + WaveFormH, waveForm->WindowColor);
      /* display new data */
      for(int16_t j = 0; j < waveForm->Channel; j++)
        OLED_DrawPixel(WaveWindowX + i, WaveWindowY + WavePic[j][i], waveForm->PointColor[j]);
    }
    for(int16_t j = 0; j < waveForm->Channel; j++)
      OLED_DrawPixel(WaveWindowX, WaveWindowY + WavePic[j][0], waveForm->BackColor);
    /* plot window line */
    OLED_DrawLineX(WaveWindowX,                 WaveWindowY,                  WaveFormW,  waveForm->WindowColor);
    OLED_DrawLineX(WaveWindowX,                 WaveWindowY + WaveForm2H - 1, WaveFormW,  waveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX,                 WaveWindowY,                  WaveForm2H, waveForm->WindowColor);
    OLED_DrawLineY(WaveWindowX + WaveFormW - 1, WaveWindowY,                  WaveForm2H, waveForm->WindowColor);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
