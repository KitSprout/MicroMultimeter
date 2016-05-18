/* #include "uMultimeter_probe.h" */

#ifndef __UMULTIMETER_PROBE_H
#define __UMULTIMETER_PROBE_H

#include "stm32f30x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define UM_PROBE_PULSE  TIMx_PWM_PULSE
#define UM_PROBE_PERI   TIMx_PWM_PERI
#define UM_PROBE_DUTY   TIMx_PWM_DUTY
#define UM_PROBE_ON     PWM_MAX
#define UM_PROBE_OFF    PWM_MIN
/*====================================================================================================*/
/*====================================================================================================*/
void     UM_PROBE_Config( void );

void     UM_ProbeOCH_Cmd( FunctionalState state );
void     UM_ProbeOCH_SetDuty( uint16_t duty );
void     UM_ProbeOCH_SetFreq( uint32_t freq );
uint16_t UM_ProbeOCH_GetDuty( void );
uint32_t UM_ProbeOCH_GetFreq( void );

uint16_t UM_ProbeICH_getADC( uint8_t channel );
uint16_t UM_ProbeICH_getAveADC( uint8_t channel );

uint16_t UM_PROBE_ADCtoVol( uint16_t adcData );

void UM_EXPAND_modeInit( uint32_t mode );
void UM_EXPAND_modeVol( uint32_t mode );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
