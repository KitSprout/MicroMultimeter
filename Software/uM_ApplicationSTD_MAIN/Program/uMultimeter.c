/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
#include "drivers\stm32f3_adc.h"
#include "modules\module_buzzer.h"
#include "algorithms\algorithm_mathUnit.h"
#include "applications\app_waveForm.h"

#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "uMultimeter_probe.h"
#include "uMultimeter_expand.h"
/*====================================================================================================*/
/*====================================================================================================*/
WaveForm_Struct WaveForm;

#define DEFAULT_MODE MODE_VOL

void UM_Run( void );
/*====================================================================================================*/
/*====================================================================================================*/
void UM_Init( void )
{
  SystemInit();
  HAL_InitTick();

  UM_GPIO_Config();
  UM_BUZZER_Config();
  UM_OLED_Config();
  UM_PROBE_Config();

	WaveForm.Channel       = 2;
	WaveForm.WindowColor   = WHITE;
	WaveForm.BackColor     = BLACK;
	WaveForm.Scale[0]      = 100;
	WaveForm.Scale[1]      = 100;
	WaveForm.PointColor[0] = GREEN;
	WaveForm.PointColor[1] = BLUE;
  WaveFormInit(&WaveForm);
  OLED_Clear(BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
void UM_Loop( void )
{
  while(1) {
    UM_Run();
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
void modeVOL_Init( uint32_t mode );
void modeVOL_CH1( void );
void modeVOL_CH2( void );
void modeVOL_DIF( void );

void modeRES_Init( uint32_t mode );
void modeRES_RES( void );
void modeRES_DIO( void );

void modePWM_Init( uint32_t mode );
void modePWM_OUT( void );
void modePWM_IN( void );

void modeWAV_Init( uint32_t mode );
void modeWAV_CH1( void );
void modeWAV_CH2( void );
void modeWAV_ALL( void );
void modeWAV_EXP( void );

void modeEXP_Init( uint32_t mode );
void modeEXP_NUL( void );

struct menuItem_st itemVOL[MODE_VOL_MAX] = {
  {MODE_VOL_CH1, &modeVOL_CH1},
  {MODE_VOL_CH2, &modeVOL_CH2},
  {MODE_VOL_DIF, &modeVOL_DIF},
};
struct menuItem_st itemRES[MODE_RES_MAX] = {
  {MODE_RES_RES, &modeRES_RES},
  {MODE_RES_DIO, &modeRES_DIO},
};
struct menuItem_st itemPWM[MODE_PWM_MAX] = {
  {MODE_PWM_OUT, &modePWM_OUT},
  {MODE_PWM_IN,  &modePWM_IN},
};
struct menuItem_st itemWAV[MODE_WAV_MAX] = {
  {MODE_WAV_CH1, &modeWAV_CH1},
  {MODE_WAV_CH2, &modeWAV_CH2},
  {MODE_WAV_ALL, &modeWAV_ALL},
  {MODE_WAV_EXP, &modeWAV_EXP},
};
struct menuItem_st itemEXP[MODE_EXP_MAX] = {
  {MODE_EXP_NUL,  &modeEXP_NUL},
//  {MODE_EXP_POW,  &modeEXP_POW},
//  {MODE_EXP_POT,  &modeEXP_POT},
//  {MODE_EXP_CUR,  &modeEXP_CUR},
//  {MODE_EXP_ADC,  &modeEXP_ADC},
//  {MODE_EXP_DAC,  &modeEXP_DAC},
//  {MODE_EXP_MOI,  &modeEXP_MOI},
//  {MODE_EXP_ROT,  &modeEXP_ROT},
//  {MODE_EXP_MAG,  &modeEXP_MAG},
//  {MODE_EXP_IMU,  &modeEXP_IMU},
//  {MODE_EXP_BMP,  &modeEXP_BMP},
//  {MODE_EXP_TEMP, &modeEXP_TEMP},
//  {MODE_EXP_RFLW, &modeEXP_RFLW},
};

struct menuPage_st menuPage[MODE_BDR_MAX] = {
  {MODE_VOL_DIF, 0, itemVOL, MODE_VOL_MAX, modeVOL_Init},
  {MODE_RES_DIO, 0, itemRES, MODE_RES_MAX, modeRES_Init},
  {MODE_PWM_IN,  0, itemPWM, MODE_PWM_MAX, modePWM_Init},
  {MODE_WAV_ALL, 0, itemWAV, MODE_WAV_MAX, modeWAV_Init},
  {MODE_EXP_NUL, 0, itemEXP, MODE_EXP_MAX, modeEXP_Init},
};

struct menuPage_st topPage = {DEFAULT_MODE, menuPage, 0, 0, UM_UI_menuDisplay};

void modeVOL_Init( uint32_t mode )
{
  UM_EXPAND_modeInit(MODE_VOL);
  UM_ProbeOCH_Cmd(ENABLE);
  Buzzer_cmd(DISABLE);

  UM_EXPAND_modeVol(mode);
  UM_UI_modeVOL_Init(mode);
  itemVOL[mode].pFunc();
}
void modeVOL_CH1( void )
{
  uint32_t tmpData = 0;
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  readData[1] = UM_ProbeICH_getAveADC(2);
  tmpData = UM_PROBE_ADCtoVol(readData[0]);
  UM_UI_modeVOL(readData[0], readData[1], tmpData);
}
void modeVOL_CH2( void )
{
  uint32_t tmpData = 0;
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  readData[1] = UM_ProbeICH_getAveADC(2);
  tmpData = UM_PROBE_ADCtoVol(readData[1]);
  UM_UI_modeVOL(readData[0], readData[1], tmpData);
}
void modeVOL_DIF( void )
{
  uint32_t tmpData = 0;
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  readData[1] = UM_ProbeICH_getAveADC(2);
  if(readData[0] > readData[1])
    tmpData = UM_PROBE_ADCtoVol(readData[0] - readData[1]);
  else
    tmpData = UM_PROBE_ADCtoVol(readData[1] - readData[0]);
  UM_UI_modeVOL(readData[0], readData[1], tmpData);
}

void modeRES_Init( uint32_t mode )
{
  UM_EXPAND_modeInit(MODE_RES);
  UM_ProbeOCH_Cmd(ENABLE);
  Buzzer_cmd(ENABLE);

  UM_UI_modeRES_Init(mode);
  itemRES[mode].pFunc();
}
void modeRES_RES( void )
{
  uint8_t state = 0;
  uint32_t tmpData = 0;
//  uint32_t readData[2] = {0};

//  readData[0] = ProbeICH_ReadAveADC(0);
//  state = Buzzer_comp(readData[0], 50);
//  tmpData = uM_measure_ADCtoRes(readData[0]);
  UM_UI_modeRES_RES(tmpData, state);
}
void modeRES_DIO( void )
{
  uint8_t state = 0;
  uint32_t tmpData = 0;
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  state = Buzzer_comp(readData[0], 50);
  tmpData = UM_PROBE_ADCtoVol(readData[0]);
  UM_UI_modeRES_DIO(tmpData, state);
}

void modePWM_Init( uint32_t mode )
{
  UM_EXPAND_modeInit(MODE_PWM);
//  UM_ProbeOCH_Cmd(DISABLE);

  UM_UI_modePWM_Init(mode);
  itemPWM[mode].pFunc();
}
void modePWM_OUT( void )
{
//  ProbeOCH_SetDuty(2000);

  // DEMO MODE
//  static uint8_t satae = 0;
//  static uint16_t i = 0;

//  i = satae ? i - 50 : i + 50;
//  if(i == 10000)  satae = 1;
//  if(i == 0)      satae = 0;

//  ProbeOCH_SetDuty(i);

//  UM_UI_modePWM(ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
}
void modePWM_IN( void )
{
//  UM_UI_modePWM(ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
}

void modeWAV_Init( uint32_t mode )
{
  UM_EXPAND_modeInit(MODE_WAV);
  UM_ProbeOCH_Cmd(DISABLE);
  UM_UI_modeWAV_Init(mode);
  itemWAV[mode].pFunc();
}
void modeWAV_CH1( void )
{
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  readData[1] = UM_ProbeICH_getAveADC(2);
  WaveForm.Data[0] = UM_PROBE_ADCtoVol(readData[0]);
  UM_UI_modeWAV_CH1(&WaveForm);
}
void modeWAV_CH2( void )
{
  uint16_t readData[2] = {0};

  readData[0] = UM_ProbeICH_getAveADC(1);
  readData[1] = UM_ProbeICH_getAveADC(2);
  WaveForm.Data[0] = UM_PROBE_ADCtoVol(readData[1]);
  UM_UI_modeWAV_CH2(&WaveForm);
}
void modeWAV_ALL( void )
{
  // DEMO
  float data = 0.0f;
  static float rad = 0.0f;

  rad += 0.05f;
  for(uint8_t i = 1; i < 10; i = i + 2)
    data += (1.0f / i) * sinf(i * rad);

  WaveForm.Data[0] = sinf(rad) * 2300;
  WaveForm.Data[1] = data * 2300;
  UM_UI_modeWAV_ALL(&WaveForm);
}
void modeWAV_EXP( void )
{
//  uint32_t readData[2] = {0};

//  readData[0] = ProbeICH_ReadAveADC(0);
//  readData[1] = ProbeICH_ReadAveADC(1);
//  WaveForm.Data[0] = uM_measure_ADCtoVol(readData[0]);
//  WaveForm.Data[1] = uM_measure_ADCtoVol(readData[1]);
  UM_UI_modeWAV_ALL(&WaveForm);
}

void modeEXP_Init( uint32_t mode )
{
  UM_EXPAND_modeInit(MODE_EXP);
//  ProbeOCH_OutputEN(0, DISABLE);
//  ProbeOCH_OutputEN(1, DISABLE);
  UM_UI_modeEXP_Init(mode);

  switch(mode) {
    case MODE_EXP_NUL:  break;
//    case MODE_EXP_POW:  ExpPOW_Init();  break;
//    case MODE_EXP_POT:  break;
//    case MODE_EXP_CUR:  break;
//    case MODE_EXP_ADC:  break;
//    case MODE_EXP_DAC:  break;
//    case MODE_EXP_MOI:  break;
//    case MODE_EXP_ROT:  ExpROT_Init();  break;
//    case MODE_EXP_MAG:  break;
//    case MODE_EXP_IMU:  ExpIMU_Init();  break;
//    case MODE_EXP_MIC:  break;
//    case MODE_EXP_BMP:  break;
//    case MODE_EXP_TEMP: break;
//    case MODE_EXP_RFLW: break;
    default:            break;
  }

  itemEXP[mode].pFunc();
}
void modeEXP_NUL( void )
{
  
}
/*====================================================================================================*/
/*====================================================================================================*/
#define DeBounce 200
void UM_Run( void )
{
  static int8_t updateState = 1;  // 1 - Update, 0 - No Update
  static int8_t modeState_selNew = DEFAULT_MODE;
  static int8_t modeState_selOld = MODE_BDR_MIN;

  if(KEY_R_Read()) {
    modeState_selNew++;
    if(modeState_selNew == MODE_BDR_MAX)
      modeState_selNew = MODE_BDR_MIN + 1;
    delay_ms(DeBounce);
  }
  if(KEY_L_Read()) {
    modeState_selNew--;
    if(modeState_selNew == MODE_BDR_MIN)
      modeState_selNew = MODE_BDR_MAX - 1;
    delay_ms(DeBounce);
  }
  if(KEY_P_Read()) {
    if(modeState_selOld == modeState_selNew) {
      topPage.pPage[topPage.mode].mode++;
      if(topPage.pPage[topPage.mode].mode == topPage.pPage[topPage.mode].itemNum)
        topPage.pPage[topPage.mode].mode = 0;
      updateState = 1;
    }
    topPage.mode = modeState_selNew;
    delay_ms(DeBounce);
  }

  topPage.Init(Byte16(uint32_t, modeState_selNew, topPage.pPage[topPage.mode].mode));

  if((modeState_selOld != topPage.mode) || updateState) {
    modeState_selOld = topPage.mode;
    updateState = 0;
    Buzzer_beep(BUZZER_OFF);
    menuPage[topPage.mode].Init(topPage.pPage[modeState_selNew].mode);  // init
  }
  else {
    menuPage[topPage.mode].pItem[menuPage[topPage.mode].mode].pFunc(); // run
  }

//  uMultimeter_expandMode();
}
/*====================================================================================================*/
/*====================================================================================================*/
