/* #include "uMultimeter_measure.h" */

#ifndef __UMULTIMETER_MEASURE_H
#define __UMULTIMETER_MEASURE_H

#include "stm32f10x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
//PB0  - PROBE_O  // TIM3_CH3, ADC12_8
//PB1  - PROBE_I  // TIM3_CH4, ADC12_9
/*=====================================================================================================*/
/*=====================================================================================================*/
void Probe_Config( void );
void ProbeICH_ADC_Config( FunctionalState state );
void ProbeICH_PWM_Config( FunctionalState state );


void ProbeOCH_OutputEN( uint8_t channel, FunctionalState state );

void ProbeOCH_SetDuty( uint16_t duty );
void ProbeOCH_SetFreq( uint32_t freq );

uint16_t ProbeOCH_GetDuty( void );
uint32_t ProbeOCH_GetFreq( void );

uint16_t ProbeICH_ReadAveADC( uint8_t Channel );
uint16_t uMultimeter_measure_ADCtoVol( uint16_t adcData );
uint32_t uMultimeter_measure_ADCtoRes( uint16_t adcData );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
