/* #include "uMultimeter.h" */

#ifndef __UMULTIMETER_H
#define __UMULTIMETER_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_Set     _GPIO_SET(GPIOC, GPIO_Pin_15)
#define LED_R_Reset   _GPIO_RST(GPIOC, GPIO_Pin_15)
#define LED_R_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_15)
#define LED_G_Set     _GPIO_SET(GPIOC, GPIO_Pin_14)
#define LED_G_Reset   _GPIO_RST(GPIOC, GPIO_Pin_14)
#define LED_G_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_14)
#define LED_B_Set     _GPIO_SET(GPIOC, GPIO_Pin_13)
#define LED_B_Reset   _GPIO_RST(GPIOC, GPIO_Pin_13)
#define LED_B_Toggle  _GPIO_TOG(GPIOC, GPIO_Pin_13)

#define KEY_U_Read    (_GPIO_READ(GPIOA, GPIO_Pin_0) == GPIO_Pin_0)
#define KEY_D_Read    (_GPIO_READ(GPIOB, GPIO_Pin_2) == GPIO_Pin_2)
#define KEY_R_Read    (_GPIO_READ(GPIOB, GPIO_Pin_9) != GPIO_Pin_9)
#define KEY_P_Read    (_GPIO_READ(GPIOB, GPIO_Pin_8) != GPIO_Pin_8)
#define KEY_L_Read    (_GPIO_READ(GPIOB, GPIO_Pin_7) != GPIO_Pin_7)

#define DEFAULT_MODE  MODE_VOL

typedef enum {
  MODE_BDR_MIN = -1,
  MODE_VOL     =  0,  // ADC      H
  MODE_RES,           // ADC      L
  MODE_PWM,           // PWM_IN   H  ||| NC       PWM_O
  MODE_WAV,           // 
  MODE_EXP,           // 
  MODE_BDR_MAX,
  MODE_DEBUG,
} uM_mode;

typedef enum {
  MODES_VOL_MIN = -1,
  MODES_VOL_CH1 =  0,
  MODES_VOL_CH2,
  MODES_VOL_DIF,
  MODES_VOL_MAX,

  MODES_RES_MIN,
  MODES_RES_RES,
  MODES_RES_DIO,
  MODES_RES_MAX,

  MODES_PWM_MIN,
  MODES_PWM_OUT,
  MODES_PWM_IN,
  MODES_PWM_MAX,

  MODES_WAV_MIN,
  MODES_WAV_ALL,
  MODES_WAV_CH1,
  MODES_WAV_CH2,
  MODES_WAV_MAX,

  MODES_EXP_MIN,
  MODES_EXP,
  MODES_EXP_MAX,
} uM_modeS;
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeter( void );
void uMultimeter_SystemInit( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
