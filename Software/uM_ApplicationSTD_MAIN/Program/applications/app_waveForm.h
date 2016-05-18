/* #include "app_waveForm.h" */

#ifndef __APP_WAVEFORM_H
#define __APP_WAVEFORM_H

#include "stm32f30x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define WaveChannelMax  2
#define WaveWindowX     0
#define WaveWindowY     6
#define WaveFormW       96
#define WaveFormH       24
#define WaveForm2H      48
/*=====================================================================================================*/
/*=====================================================================================================*/
typedef struct {
  uint8_t  Channel;
  int16_t  Data[WaveChannelMax];
  uint16_t Scale[WaveChannelMax];
  uint32_t PointColor[WaveChannelMax];
  uint32_t WindowColor;
  uint32_t BackColor;
} WaveForm_Struct;
/*=====================================================================================================*/
/*=====================================================================================================*/
void WaveFormInit( WaveForm_Struct *pWaveForm );
void WaveFormPrint( WaveForm_Struct *pWaveForm, uint8_t display );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
