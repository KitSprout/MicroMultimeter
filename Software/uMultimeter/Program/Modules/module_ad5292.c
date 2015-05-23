/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_ad5292.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define AD5292_SPIx           SPI2
#define AD5292_SPIx_CLK       RCC_APB1Periph_SPI2

#define AD5292_CS_PIN         GPIO_Pin_12
#define AD5292_CS_GPIO_PORT   GPIOB
#define AD5292_CS_GPIO_CLK    RCC_APB2Periph_GPIOB
#define AD5292_CS_H           GPIO_SetBits(AD5292_CS_GPIO_PORT, AD5292_CS_PIN)
#define AD5292_CS_L           GPIO_ResetBits(AD5292_CS_GPIO_PORT, AD5292_CS_PIN)

#define AD5292_SCK_PIN        GPIO_Pin_13
#define AD5292_SCK_GPIO_PORT  GPIOB
#define AD5292_SCK_GPIO_CLK   RCC_APB2Periph_GPIOB

#define AD5292_SDO_PIN        GPIO_Pin_14
#define AD5292_SDO_GPIO_PORT  GPIOB
#define AD5292_SDO_GPIO_CLK   RCC_APB2Periph_GPIOB

#define AD5292_SDI_PIN        GPIO_Pin_15
#define AD5292_SDI_GPIO_PORT  GPIOB
#define AD5292_SDI_GPIO_CLK   RCC_APB2Periph_GPIOB
/*====================================================================================================*/
/*====================================================================================================*
**函數 : AD5292_Config
**功能 : 配置 IO
**輸入 : None
**輸出 : None
**使用 : AD5292_Config();
**====================================================================================================*/
/*====================================================================================================*/
void AD5292_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init *************************************************************/
  RCC_APB1PeriphClockCmd(AD5292_SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(AD5292_CS_GPIO_CLK  | AD5292_SCK_GPIO_CLK | AD5292_SDO_GPIO_CLK |
                         AD5292_SDI_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

  /* CS  */
  GPIO_InitStruct.GPIO_Pin = AD5292_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(AD5292_CS_GPIO_PORT, &GPIO_InitStruct);
  /* SCK */
  GPIO_InitStruct.GPIO_Pin = AD5292_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(AD5292_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDO */
  GPIO_InitStruct.GPIO_Pin = AD5292_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(AD5292_SDO_GPIO_PORT, &GPIO_InitStruct);
  /* SDI */
  GPIO_InitStruct.GPIO_Pin = AD5292_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(AD5292_SDI_GPIO_PORT, &GPIO_InitStruct);

  AD5292_CS_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_16b;                   // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;                           // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;  // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(AD5292_SPIx, &SPI_InitStruct);

  SPI_Cmd(AD5292_SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : AD5292_Init
**功能 : AD5292 Init
**輸入 : None
**輸出 : None
**使用 : AD5292_Init();
**====================================================================================================*/
/*====================================================================================================*/
void AD5292_Init( void )
{
  AD5292_CS_L;
  SPI_RW(AD5292_SPIx, AD5292_CMD_WRITE_CTRL | AD5292_CTRL_RDAC_UPDATE);
  AD5292_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : AD5292_WriteRDAC
**功能 : Write RDAC
**輸入 : None
**輸出 : None
**使用 : AD5292_WriteRDAC(512);
**====================================================================================================*/
/*====================================================================================================*/
void AD5292_WriteRDAC( uint16_t WriteData )
{
  AD5292_CS_L;
  SPI_RW(AD5292_SPIx, AD5292_CMD_WRITE_RDAC | (WriteData & 0x03FF));
  AD5292_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*/
