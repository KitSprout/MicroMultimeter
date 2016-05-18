/* #include "module_buzzer.h" */

#ifndef __MODULE_BUZZER_H
#define __MODULE_BUZZER_H

#include "stm32f30x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define BUZZER_MIN  ((uint16_t)0)
#define BUZZER_MED  ((uint16_t)1250)
#define BUZZER_MAX  ((uint16_t)2500)

#define BUZZER_ON   BUZZER_MED
#define BUZZER_OFF  BUZZER_MIN
/*====================================================================================================*/
/*====================================================================================================*/
void    Buzzer_Config( void );
void    Buzzer_cmd( uint8_t cmd );
void    Buzzer_setLoudness( uint16_t loudness );
void    Buzzer_beep( uint16_t loudness );
uint8_t Buzzer_comp( uint16_t readData, uint16_t threshold );

void    Buzzer_test( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
