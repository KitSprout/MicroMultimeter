/* #include "uMultimeter_ui.h" */

#ifndef __UMULTIMETER_UI_H
#define __UMULTIMETER_UI_H

#include "stm32f10x.h"
#include "uMultimeter.h"
#include "api_waveForm.h"
/*====================================================================================================*/
/*====================================================================================================*/
typedef enum {
  MODE_BDR_MIN  = -1,
  MODE_VOL      =  0,  // ADC      H
  MODE_RES,           // ADC      L
  MODE_PWM,           // PWM_IN   H  ||| NC       PWM_O
  MODE_WAV,           // 
  MODE_EXP,           // 
  MODE_BDR_MAX,
  MODE_DEBUG,
} uM_mode;

typedef enum {
  MODE_VOL_MIN = -1,
  MODE_VOL_CH1 =  0,
  MODE_VOL_CH2,
  MODE_VOL_DIF,
  MODE_VOL_MAX,
  MODE_VOL_DEBUG,
} uM_modeVOL;

typedef enum {
  MODE_RES_MIN = -1,
  MODE_RES_RES =  0,
  MODE_RES_DIO,
  MODE_RES_MAX,
  MODE_RES_DEBUG,
} uM_modeRES;

typedef enum {
  MODE_PWM_MIN = -1,
  MODE_PWM_OUT =  0,
  MODE_PWM_IN,
  MODE_PWM_MAX,
  MODE_PWM_DEBUG,
} uM_modePWM;

typedef enum {
  MODE_WAV_MIN = -1,
  MODE_WAV_CH1 =  0,
  MODE_WAV_CH2,
  MODE_WAV_ALL,
  MODE_WAV_EXP,
  MODE_WAV_MAX,
  MODE_WAV_DEBUG,
} uM_modeWAV;

typedef enum {
  MODE_EXP_MIN = -1,
  MODE_EXP_NUL =  0,
  MODE_EXP_POW,
//  MODE_EXP_POT,
//  MODE_EXP_CUR,
//  MODE_EXP_ADC,
//  MODE_EXP_DAC,
//  MODE_EXP_MOI,
  MODE_EXP_ROT,
//  MODE_EXP_MAG,
  MODE_EXP_IMU,
//  MODE_EXP_MIC,
//  MODE_EXP_BMP,
//  MODE_EXP_TEMP,
//  MODE_EXP_RFLW,
  MODE_EXP_MAX,
  MODE_EXP_DEBUG,
} uM_modeEXP;

struct menuItem_st{
	int8_t index;
	void (*pFunc)( void );
};

struct menuPage_st{
	int8_t mode;
  struct menuPage_st *pPage;
  const struct menuItem_st *pItem;
  const uint8_t itemNum;
  void (*Init)( uint32_t );
};
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeterUI_menuDisplay( uint32_t modeS );

void uMultimeterUI_modeVOL_Init( uint8_t mode );
void uMultimeterUI_modeVOL( uint16_t NumCH1, uint16_t NumCH2, uint16_t BigNum );

void uMultimeterUI_modeRES_Init( uint8_t mode );
void uMultimeterUI_modeRES_RES( uint32_t BigNum, uint8_t BeepState );
void uMultimeterUI_modeRES_DIO( uint32_t BigNum, uint8_t BeepState );

void uMultimeterUI_modePWM_Init( uint8_t modeS );
void uMultimeterUI_modePWM( uint16_t DutyData, uint32_t FreqData );

void uMultimeterUI_modeWAV_Init( uint8_t modeS );
void uMultimeterUI_modeWAV_CH1( WaveForm_Struct *pWaveForm );
void uMultimeterUI_modeWAV_CH2( WaveForm_Struct *pWaveForm );
void uMultimeterUI_modeWAV_ALL( WaveForm_Struct *pWaveForm );

void uMultimeterUI_modeEXP_Init( uint8_t modeS );
void uMultimeterUI_modeEXP( uint8_t modeS );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
