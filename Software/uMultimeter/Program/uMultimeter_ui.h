/* #include "uMultimeter_ui.h" */

#ifndef __UMULTIMETER_UI_H
#define __UMULTIMETER_UI_H

#include "stm32f10x.h"
#include "uMultimeter.h"
#include "api_waveForm.h"
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeterUI_modeVOL_Init( uM_modeS modeS );
void uMultimeterUI_modeVOL( uM_modeS modeS, uint16_t NumCH1, uint16_t NumCH2, uint16_t BigNum );
void uMultimeterUI_modeVOL_setMode( uint8_t mode );

void uMultimeterUI_modeRES_Init( uM_modeS modeS );
void uMultimeterUI_modeRES( uM_modeS modeS, uint32_t BigNum, uint8_t BeepState );
void uMultimeterUI_modeRES_setMode( uM_modeS modeS );

void uMultimeterUI_modePWM_Init( uM_modeS modeS );
void uMultimeterUI_modePWM( uM_modeS modeS, uint16_t DutyData, uint32_t FreqData );

void uMultimeterUI_modeWAV_Init( uM_modeS modeS );
void uMultimeterUI_modeWAV( uM_modeS modeS, WaveForm_Struct *WaveForm );

void uMultimeterUI_modeEXP_Init( uM_modeS modeS );
void uMultimeterUI_modeEXP( uM_modeS modeS );

void uMultimeterUI_menuDisplay( uM_mode mode, uM_modeS modeS );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
