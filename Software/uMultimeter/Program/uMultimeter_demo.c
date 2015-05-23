/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "uMultimeter_measure.h"
#include "uMultimeter_demo.h"
#include "api_waveForm.h"
#include "exp_digiGPIO.h"
#include "exp_digiPower.h"
#include "module_buzzer.h"
#include "module_ssd1331.h"
#include "algorithm_mathUnit.h"
/*====================================================================================================*/
/*====================================================================================================*/
extern WaveForm_Struct WaveForm;
extern const uM_modeS modeState_selS_MAX_MIN[5][2];
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_demoMode_Init( uM_mode mode, uM_modeS modeS )
{
  Buzzer_cmd(DISABLE);
  switch(mode) {
    case MODE_VOL:
      ProbeOCH_OutputEN(0, DISABLE);
      ProbeOCH_OutputEN(1, DISABLE);
      uMultimeterUI_modeVOL_Init(modeS);
      break;
    case MODE_RES:
      ProbeOCH_OutputEN(0, ENABLE);
      ProbeOCH_OutputEN(1, DISABLE);
      uMultimeterUI_modeRES_Init(modeS);
      break;
    case MODE_PWM:
      ProbeOCH_OutputEN(0, ENABLE);
      ProbeOCH_OutputEN(1, DISABLE);
      uMultimeterUI_modePWM_Init(modeS);
      break;
    case MODE_WAV:
      ProbeOCH_OutputEN(0, DISABLE);
      ProbeOCH_OutputEN(1, DISABLE);
      uMultimeterUI_modeWAV_Init(modeS);
      break;
    case MODE_EXP:
      ProbeOCH_OutputEN(0, DISABLE);
      ProbeOCH_OutputEN(1, DISABLE);
      uMultimeterUI_modeEXP_Init(modeS);
      break;
    case MODE_DEBUG:
      break;
    default:
      return;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_DemoPWM( uM_modeS modeS )
{
  static uint8_t satae = 0;
  static uint16_t i = 0;

  i = satae ? i - 50 : i + 50;
  if(i == 10000)  satae = 1;
  if(i == 0)      satae = 0;

  ProbeOCH_SetDuty(i);
}
void uMultimeter_DemoWAV( WaveForm_Struct *WaveForm )
{
  uint16_t readData = 0;
  static int32_t theta = 0;

  theta += 2;
  if(theta == 180) theta = 0;

  readData = ProbeICH_ReadAveADC(0);
  WaveForm->Data[0] = uMultimeter_measure_ADCtoVol(readData);
  WaveForm->Data[1] = arm_sin_f32(toRad(theta)) * 4600;
}
void uMultimeter_demoMode_Run( uM_mode mode, uM_modeS modeS )
{
  uint8_t state = 0;
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  switch(mode) {

    case MODE_VOL:
      readData[0] = ProbeICH_ReadAveADC(0);
      readData[1] = ProbeICH_ReadAveADC(1);
      if(modeS == MODES_VOL_CH1)
        tmpData = uMultimeter_measure_ADCtoVol(readData[0]);
      else if(modeS == MODES_VOL_CH2)
        tmpData = uMultimeter_measure_ADCtoVol(readData[1]);
      else
        tmpData = (readData[0] > readData[1]) ? uMultimeter_measure_ADCtoVol(readData[0] - readData[1]) : uMultimeter_measure_ADCtoVol(readData[1] - readData[0]);
      uMultimeterUI_modeVOL(modeS, readData[0], readData[1], tmpData);
      break;

    case MODE_RES:
      readData[0] = ProbeICH_ReadAveADC(0);
      state = Buzzer_cmp(readData[0], 50);
      if(modeS == MODES_RES_RES)
        tmpData = uMultimeter_measure_ADCtoRes(readData[0]);
      else
        tmpData = uMultimeter_measure_ADCtoVol(readData[0]);
      uMultimeterUI_modeRES(modeS, tmpData, state);
      break;

    case MODE_PWM:
      uMultimeter_DemoPWM(modeS);
      uMultimeterUI_modePWM(modeS, ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
      break;

    case MODE_WAV:
      uMultimeter_DemoWAV(&WaveForm);
      uMultimeterUI_modeWAV(modeS, &WaveForm);
      
      break;

    case MODE_EXP:
      uMultimeterUI_modeEXP(modeS);
      break;

    case MODE_DEBUG:
      break;

    default:
      return;
  }
}

#define DeBounce 20
void uMultimeter_demo( void )
{
  static uM_mode  modeState_move = DEFAULT_MODE;
  static uM_mode  modeState_selNew = DEFAULT_MODE;
  static uM_mode  modeState_selOld = MODE_BDR_MIN;
  static uM_modeS modeState_selS[5] = { MODES_VOL_DIF, MODES_RES_RES, MODES_PWM_OUT, MODES_WAV_ALL, MODES_EXP };

  while(KEY_R_Read) {
    modeState_move++;
    if(modeState_move == MODE_BDR_MAX)
      modeState_move = (uM_mode)(MODE_BDR_MIN + 1);
    Delay_10ms(DeBounce);
  }
  while(KEY_L_Read) {
    modeState_move--;
    if(modeState_move == MODE_BDR_MIN)
      modeState_move = (uM_mode)(MODE_BDR_MAX - 1);
    Delay_10ms(DeBounce);
  }
  if(KEY_P_Read) {
    if(modeState_selOld == modeState_move) {
      modeState_selS[modeState_move]++;
      if(modeState_selS[modeState_move] == modeState_selS_MAX_MIN[modeState_move][1])
        modeState_selS[modeState_move] = (uM_modeS)(modeState_selS_MAX_MIN[modeState_move][0] + 1);
    }
    modeState_selNew = modeState_move;
    Delay_10ms(DeBounce);
  }

  uMultimeterUI_menuDisplay(modeState_move, modeState_selS[modeState_move]);

  if(modeState_selOld != modeState_selNew) {
    modeState_selOld = modeState_selNew;
    uMultimeter_demoMode_Init(modeState_selNew, modeState_selS[modeState_selNew]);
  }
  else {
    uMultimeter_demoMode_Run(modeState_selNew, modeState_selS[modeState_selNew]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
