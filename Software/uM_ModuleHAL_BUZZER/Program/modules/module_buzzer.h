/* #include "module_buzzer.h" */

#ifndef __MODULE_BUZZER_H
#define __MODULE_BUZZER_H

#include "stm32f3xx_hal.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define BUZZER_MIN  0
#define BUZZER_MED  1250
#define BUZZER_MAX  2500

#define BUZZER_ON   BUZZER_MED
#define BUZZER_OFF  BUZZER_MIN
/*====================================================================================================*/
/*====================================================================================================*/
void Buzzer_Config( void );
void Buzzer_cmd( uint8_t cmd );
void Buzzer_setLoudness( uint8_t loudness );
void Buzzer_beep( uint8_t loudness );
void Buzzer_comp( uint16_t readData, uint16_t threshold );
void Buzzer_test( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
