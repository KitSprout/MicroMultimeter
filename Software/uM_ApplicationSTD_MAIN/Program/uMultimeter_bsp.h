/* #include "umultimeter_bsp.h" */

#ifndef __UMULTIMETER_BSP_H
#define __UMULTIMETER_BSP_H

#include "stm32f30x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define LED_R_PIN                 GPIO_Pin_11
#define LED_R_GPIO_PORT           GPIOB
#define LED_R_Set()               __GPIO_SET(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Reset()             __GPIO_RST(LED_R_GPIO_PORT, LED_R_PIN)
#define LED_R_Toggle()            __GPIO_TOG(LED_R_GPIO_PORT, LED_R_PIN)

#define LED_G_PIN                 GPIO_Pin_0
#define LED_G_GPIO_PORT           GPIOB
#define LED_G_Set()               __GPIO_SET(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Reset()             __GPIO_RST(LED_G_GPIO_PORT, LED_G_PIN)
#define LED_G_Toggle()            __GPIO_TOG(LED_G_GPIO_PORT, LED_G_PIN)

#define LED_B_PIN                 GPIO_Pin_12
#define LED_B_GPIO_PORT           GPIOB
#define LED_B_Set()               __GPIO_SET(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Reset()             __GPIO_RST(LED_B_GPIO_PORT, LED_B_PIN)
#define LED_B_Toggle()            __GPIO_TOG(LED_B_GPIO_PORT, LED_B_PIN)

#define KEY_U_PIN                 GPIO_Pin_2
#define KEY_U_GPIO_PORT           GPIOB
#define KEY_U_Read()              (__GPIO_READ(KEY_U_GPIO_PORT, KEY_U_PIN) == KEY_U_PIN)

#define KEY_D_PIN                 GPIO_Pin_10
#define KEY_D_GPIO_PORT           GPIOB
#define KEY_D_Read()              (__GPIO_READ(KEY_D_GPIO_PORT, KEY_D_PIN) == KEY_D_PIN)

#define KEY_R_PIN                 GPIO_Pin_15
#define KEY_R_GPIO_PORT           GPIOC
#define KEY_R_Read()              (__GPIO_READ(KEY_R_GPIO_PORT, KEY_R_PIN) != KEY_R_PIN)

#define KEY_P_PIN                 GPIO_Pin_14
#define KEY_P_GPIO_PORT           GPIOC
#define KEY_P_Read()              (__GPIO_READ(KEY_P_GPIO_PORT, KEY_P_PIN) != KEY_P_PIN)

#define KEY_L_PIN                 GPIO_Pin_13
#define KEY_L_GPIO_PORT           GPIOC
#define KEY_L_Read()              (__GPIO_READ(KEY_L_GPIO_PORT, KEY_L_PIN) != KEY_L_PIN)
/*====================================================================================================*/
/*====================================================================================================*/
void UM_GPIO_Config( void );
void UM_BUZZER_Config( void );
void UM_OLED_Config( void );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
