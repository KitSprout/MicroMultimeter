/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "api_waveForm.h"
#include "exp_digiGPIO.h"
#include "uMultimeter_measure.h"
#include "exp_digiPower.h"
#include "module_buzzer.h"
#include "module_ssd1331.h"
#include "algorithm_mathUnit.h"
/*====================================================================================================*/
/*====================================================================================================*/
WaveForm_Struct WaveForm;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIO_Config
**功能 : LED and KEY Config
**輸入 : None
**輸出 : None
**使用 : GPIO_Config();
**====================================================================================================*/
/*====================================================================================================*/
static void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  /* LED Config */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY Config */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_SystemInit
**功能 : uMultimeter Init
**輸入 : None
**輸出 : None
**使用 : uMultimeter_SystemInit();
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_SystemInit( void )
{
  GPIO_Config();
  Buzzer_Config();
  SSD1331_Config();
  Probe_Config();

  ExpGPIO_Config();

  Buzzer_setLoudness(60);
  SSD1331_Init();

	WaveForm.Channel = 2;
	WaveForm.WindowColor = WHITE;
	WaveForm.BackColor = BLACK;
	WaveForm.Data[0] = 0;
	WaveForm.Data[1] = 0;
	WaveForm.Scale[0] = 100;
	WaveForm.Scale[1] = 100;
	WaveForm.PointColor[0] = GREEN;
	WaveForm.PointColor[1] = BLUE;

  OLED_Clear(BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_expandMode
**功能 : 
**輸入 : None
**輸出 : None
**使用 : 
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_expandMode( void )
{
// 0, 0 -> I/O
// 0, 1 -> UART
// 1, 0 -> SPI
// 1, 1 -> I2C
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_measureMode_Init
**功能 : 
**輸入 : mode, modeS
**輸出 : None
**使用 : uMultimeter_measureMode_Init(mode, modeS);
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_measureMode_Init( uM_mode mode, uM_modeS modeS )
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
/*====================================================================================================*
**函數 : uMultimeter_measureMode_Init
**功能 : 
**輸入 : mode, modeS
**輸出 : None
**使用 : uMultimeter_measureMode_Run(mode, modeS);
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_measureMode_Run( uM_mode mode, uM_modeS modeS )
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
      ProbeOCH_SetDuty(2000);
      uMultimeterUI_modePWM(modeS, ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
      break;

    case MODE_WAV:
      readData[0] = ProbeICH_ReadAveADC(0);
      readData[1] = ProbeICH_ReadAveADC(1);
      WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
      WaveForm.Data[1] = uMultimeter_measure_ADCtoVol(readData[1]);
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
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter
**功能 : 
**輸入 : None
**輸出 : None
**使用 : uMultimeter();
**====================================================================================================*/
/*====================================================================================================*/
#define DeBounce 20
const uM_modeS  modeState_selS_MAX_MIN[5][2] = {
  {MODES_VOL_MIN, MODES_VOL_MAX},
  {MODES_RES_MIN, MODES_RES_MAX},
  {MODES_PWM_MIN, MODES_PWM_MAX},
  {MODES_WAV_MIN, MODES_WAV_MAX},
  {MODES_EXP_MIN, MODES_EXP_MAX},
};
void uMultimeter( void )
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
    uMultimeter_measureMode_Init(modeState_selNew, modeState_selS[modeState_selNew]);
  }
  else {
    uMultimeter_measureMode_Run(modeState_selNew, modeState_selS[modeState_selNew]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
