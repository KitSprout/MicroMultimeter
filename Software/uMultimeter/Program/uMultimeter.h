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
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeter( void );
void uMultimeter_SystemInit( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
