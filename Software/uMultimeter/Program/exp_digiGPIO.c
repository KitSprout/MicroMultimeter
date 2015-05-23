/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "exp_digiGPIO.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
/*
PB10 - EXT_01   // UART3_TX, I2C2_SCL, TIM2_CH3
PB11 - EXT_02   // UART3_RX, I2C2_SDA, TIM2_CH4
PB12 - EXT_03   // SPI2_NSS, UART3_CK
PB13 - EXT_04   // SPI2_SCK, UART3_CT
PB14 - EXT_05   // SPI2_MISO, UART3_RT
PB15 - EXT_06   // SPI2_MOSI
PA8  - EXT_07   // TIM1_CH1
PA9  - EXT_08   // TIM1_CH2, UART1_TX
*/

#define EXP_CH1_GPIO_PIN    GPIO_Pin_10
#define EXP_CH1_GPIO_PORT   GPIOB
#define EXP_CH1_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH1_Set         _GPIO_SET(EXP_CH1_GPIO_PORT, EXP_CH1_GPIO_PIN)
#define EXP_CH1_Reset       _GPIO_RST(EXP_CH1_GPIO_PORT, EXP_CH1_GPIO_PIN)
#define EXP_CH1_Toggle      _GPIO_TOG(EXP_CH1_GPIO_PORT, EXP_CH1_GPIO_PIN)
#define EXP_CH1_Read        (_GPIO_READ(EXP_CH1_GPIO_PORT, EXP_CH1_GPIO_PIN) != EXP_CH1_GPIO_PIN)

#define EXP_CH2_GPIO_PIN    GPIO_Pin_11
#define EXP_CH2_GPIO_PORT   GPIOB
#define EXP_CH2_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH2_Set         _GPIO_SET(EXP_CH2_GPIO_PORT, EXP_CH2_GPIO_PIN)
#define EXP_CH2_Reset       _GPIO_RST(EXP_CH2_GPIO_PORT, EXP_CH2_GPIO_PIN)
#define EXP_CH2_Toggle      _GPIO_TOG(EXP_CH2_GPIO_PORT, EXP_CH2_GPIO_PIN)
#define EXP_CH2_Read        (_GPIO_READ(EXP_CH2_GPIO_PORT, EXP_CH2_GPIO_PIN) != EXP_CH2_GPIO_PIN)

#define EXP_CH3_GPIO_PIN    GPIO_Pin_12
#define EXP_CH3_GPIO_PORT   GPIOB
#define EXP_CH3_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH3_Set         _GPIO_SET(EXP_CH3_GPIO_PORT, EXP_CH3_GPIO_PIN)
#define EXP_CH3_Reset       _GPIO_RST(EXP_CH3_GPIO_PORT, EXP_CH3_GPIO_PIN)
#define EXP_CH3_Toggle      _GPIO_TOG(EXP_CH3_GPIO_PORT, EXP_CH3_GPIO_PIN)
#define EXP_CH3_Read        (_GPIO_READ(EXP_CH3_GPIO_PORT, EXP_CH3_GPIO_PIN) != EXP_CH3_GPIO_PIN)

#define EXP_CH4_GPIO_PIN    GPIO_Pin_13
#define EXP_CH4_GPIO_PORT   GPIOB
#define EXP_CH4_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH4_Set         _GPIO_SET(EXP_CH4_GPIO_PORT, EXP_CH4_GPIO_PIN)
#define EXP_CH4_Reset       _GPIO_RST(EXP_CH4_GPIO_PORT, EXP_CH4_GPIO_PIN)
#define EXP_CH4_Toggle      _GPIO_TOG(EXP_CH4_GPIO_PORT, EXP_CH4_GPIO_PIN)
#define EXP_CH4_Read        (_GPIO_READ(EXP_CH4_GPIO_PORT, EXP_CH4_GPIO_PIN) != EXP_CH4_GPIO_PIN)

#define EXP_CH5_GPIO_PIN    GPIO_Pin_14
#define EXP_CH5_GPIO_PORT   GPIOB
#define EXP_CH5_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH5_Set         _GPIO_SET(EXP_CH5_GPIO_PORT, EXP_CH5_GPIO_PIN)
#define EXP_CH5_Reset       _GPIO_RST(EXP_CH5_GPIO_PORT, EXP_CH5_GPIO_PIN)
#define EXP_CH5_Toggle      _GPIO_TOG(EXP_CH5_GPIO_PORT, EXP_CH5_GPIO_PIN)
#define EXP_CH5_Read        (_GPIO_READ(EXP_CH5_GPIO_PORT, EXP_CH5_GPIO_PIN) != EXP_CH5_GPIO_PIN)

#define EXP_CH6_GPIO_PIN    GPIO_Pin_15
#define EXP_CH6_GPIO_PORT   GPIOB
#define EXP_CH6_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_CH6_Set         _GPIO_SET(EXP_CH6_GPIO_PORT, EXP_CH6_GPIO_PIN)
#define EXP_CH6_Reset       _GPIO_RST(EXP_CH6_GPIO_PORT, EXP_CH6_GPIO_PIN)
#define EXP_CH6_Toggle      _GPIO_TOG(EXP_CH6_GPIO_PORT, EXP_CH6_GPIO_PIN)
#define EXP_CH6_Read        (_GPIO_READ(EXP_CH6_GPIO_PORT, EXP_CH6_GPIO_PIN) != EXP_CH6_GPIO_PIN)

#define EXP_CH7_GPIO_PIN    GPIO_Pin_9
#define EXP_CH7_GPIO_PORT   GPIOA
#define EXP_CH7_GPIO_CLK    RCC_APB2Periph_GPIOA
#define EXP_CH7_Set         _GPIO_SET(EXP_CH7_GPIO_PORT, EXP_CH7_GPIO_PIN)
#define EXP_CH7_Reset       _GPIO_RST(EXP_CH7_GPIO_PORT, EXP_CH7_GPIO_PIN)
#define EXP_CH7_Toggle      _GPIO_TOG(EXP_CH7_GPIO_PORT, EXP_CH7_GPIO_PIN)
#define EXP_CH7_Read        (_GPIO_READ(EXP_CH7_GPIO_PORT, EXP_CH7_GPIO_PIN) != EXP_CH7_GPIO_PIN)

#define EXP_CH8_GPIO_PIN    GPIO_Pin_10
#define EXP_CH8_GPIO_PORT   GPIOA
#define EXP_CH8_GPIO_CLK    RCC_APB2Periph_GPIOA
#define EXP_CH8_Set         _GPIO_SET(EXP_CH8_GPIO_PORT, EXP_CH8_GPIO_PIN)
#define EXP_CH8_Reset       _GPIO_RST(EXP_CH8_GPIO_PORT, EXP_CH8_GPIO_PIN)
#define EXP_CH8_Toggle      _GPIO_TOG(EXP_CH8_GPIO_PORT, EXP_CH8_GPIO_PIN)
#define EXP_CH8_Read        (_GPIO_READ(EXP_CH8_GPIO_PORT, EXP_CH8_GPIO_PIN) != EXP_CH8_GPIO_PIN)

#define EXP_ID1_GPIO_PIN    GPIO_Pin_15
#define EXP_ID1_GPIO_PORT   GPIOA
#define EXP_ID1_GPIO_CLK    RCC_APB2Periph_GPIOA
#define EXP_ID1_Set         _GPIO_SET(EXP_ID1_GPIO_PORT, EXP_ID1_GPIO_PIN)
#define EXP_ID1_Reset       _GPIO_RST(EXP_ID1_GPIO_PORT, EXP_ID1_GPIO_PIN)
#define EXP_ID1_Toggle      _GPIO_TOG(EXP_ID1_GPIO_PORT, EXP_ID1_GPIO_PIN)
#define EXP_ID1_Read        (_GPIO_READ(EXP_ID1_GPIO_PORT, EXP_ID1_GPIO_PIN) != EXP_ID1_GPIO_PIN)

#define EXP_ID2_GPIO_PIN    GPIO_Pin_3
#define EXP_ID2_GPIO_PORT   GPIOB
#define EXP_ID2_GPIO_CLK    RCC_APB2Periph_GPIOB
#define EXP_ID2_Set         _GPIO_SET(EXP_ID2_GPIO_PORT, EXP_ID2_GPIO_PIN)
#define EXP_ID2_Reset       _GPIO_RST(EXP_ID2_GPIO_PORT, EXP_ID2_GPIO_PIN)
#define EXP_ID2_Toggle      _GPIO_TOG(EXP_ID2_GPIO_PORT, EXP_ID2_GPIO_PIN)
#define EXP_ID2_Read        (_GPIO_READ(EXP_ID2_GPIO_PORT, EXP_ID2_GPIO_PIN) != EXP_ID2_GPIO_PIN)
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ExpGPIO_Config
**功能 : ExpIO and ExpID Config
**輸入 : None
**輸出 : None
**使用 : ExpGPIO_Config();
**====================================================================================================*/
/*====================================================================================================*/
void ExpGPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(EXP_CH1_GPIO_CLK | EXP_CH2_GPIO_CLK | EXP_CH3_GPIO_CLK | EXP_CH4_GPIO_CLK |
                         EXP_CH5_GPIO_CLK | EXP_CH6_GPIO_CLK | EXP_CH7_GPIO_CLK | EXP_CH8_GPIO_CLK |
                         EXP_ID1_GPIO_CLK | EXP_ID2_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* ExpIO Config */
  GPIO_InitStruct.GPIO_Pin = EXP_CH1_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH1_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH2_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH2_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH3_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH3_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH4_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH4_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH5_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH5_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH6_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH6_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH7_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH7_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_CH8_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(EXP_CH8_GPIO_PORT, &GPIO_InitStruct);

  /* ExpID Config */
  GPIO_InitStruct.GPIO_Pin = EXP_ID1_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(EXP_ID1_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = EXP_ID2_GPIO_PIN;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_Init(EXP_ID2_GPIO_PORT, &GPIO_InitStruct);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
