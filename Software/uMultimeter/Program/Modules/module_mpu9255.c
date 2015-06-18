/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_mpu9255.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define SPIx                SPI2
#define SPIx_CLK            RCC_APB1Periph_SPI2
#define SPIx_SPEED_HIGH     SPI_BaudRatePrescaler_4
#define SPIx_SPEED_LOW      SPI_BaudRatePrescaler_256

#define SPIx_CS_PIN         GPIO_Pin_12
#define SPIx_CS_GPIO_PORT   GPIOB
#define SPIx_CS_GPIO_CLK    RCC_APB2Periph_GPIOB
#define SPIx_CS_H           GPIO_SetBits(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)
#define SPIx_CS_L           GPIO_ResetBits(SPIx_CS_GPIO_PORT, SPIx_CS_PIN)

#define SPIx_SCK_PIN        GPIO_Pin_13
#define SPIx_SCK_GPIO_PORT  GPIOB
#define SPIx_SCK_GPIO_CLK   RCC_APB2Periph_GPIOB

#define SPIx_SDO_PIN        GPIO_Pin_14
#define SPIx_SDO_GPIO_PORT  GPIOB
#define SPIx_SDO_GPIO_CLK   RCC_APB2Periph_GPIOB

#define SPIx_SDI_PIN        GPIO_Pin_15
#define SPIx_SDI_GPIO_PORT  GPIOB
#define SPIx_SDI_GPIO_CLK   RCC_APB2Periph_GPIOB
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_ReadReg
**功能 : 讀暫存器
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : MPU9255_ReadReg(ReadAddr, &DeviceID);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_ReadReg( uint8_t ReadAddr, uint8_t *ReadData )
{
  SPIx_CS_L;
  SPI_RW(SPIx, 0x80 | ReadAddr);
  *ReadData = SPI_RW(SPIx, 0xFF);
  SPIx_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_WriteReg
**功能 : 寫暫存器
**輸入 : WriteAddr, WriteData
**輸出 : None
**使用 : MPU9255_WriteReg(WriteAddr, WriteData);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_WriteReg( uint8_t WriteAddr, uint8_t WriteData )
{
  SPIx_CS_L;
  SPI_RW(SPIx, WriteAddr);
  SPI_RW(SPIx, WriteData);
  SPIx_CS_H;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MPU9255_ReadRegs
**功能 : 連續讀暫存器
**輸入 : ReadAddr, *ReadBuf, Bytes
**輸出 : None
**使用 : MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, ReadBuf, 14);
**=====================================================================================================*/
/*=====================================================================================================*/
void MPU9255_ReadRegs( uint8_t ReadAddr, uint8_t *ReadBuf, uint8_t Bytes )
{
  SPIx_CS_L;
  SPI_RW(SPIx, 0x80 | ReadAddr);
  for(uint8_t i = 0; i < Bytes; i++)
    ReadBuf[i] = SPI_RW(SPIx, 0xFF);
  SPIx_CS_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_SetSpeed
**功能 : 設置 SPI 速度
**輸入 : SpeedSel
**輸出 : None
**使用 : MPU9255_SetSpeed(SPIx_SPEED_LOW);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_SetSpeed( uint8_t SpeedSel )
{
  SPI_InitTypeDef SPI_InitStruct;

  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SpeedSel;                  // SpeedSel
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx, &SPI_InitStruct);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Config
**功能 : 初始化 MPU9255
**輸入 : None
**輸出 : None
**使用 : MPU9255_Config();
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init ************************************************************/
  RCC_APB1PeriphClockCmd(SPIx_CLK, ENABLE);
  RCC_APB2PeriphClockCmd(SPIx_CS_GPIO_CLK  | SPIx_SCK_GPIO_CLK |
                         SPIx_SDO_GPIO_CLK | SPIx_SDI_GPIO_CLK, ENABLE);

  /* CS  */
  GPIO_InitStruct.GPIO_Pin = SPIx_CS_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(SPIx_CS_GPIO_PORT, &GPIO_InitStruct);
  /* SCK */
  GPIO_InitStruct.GPIO_Pin = SPIx_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDO */
  GPIO_InitStruct.GPIO_Pin = SPIx_SDO_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SDO_GPIO_PORT, &GPIO_InitStruct);
  /* SDI */
  GPIO_InitStruct.GPIO_Pin = SPIx_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(SPIx_SDI_GPIO_PORT, &GPIO_InitStruct);

  SPIx_CS_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 16 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPIx_SPEED_LOW;            // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPIx, &SPI_InitStruct);

  SPI_Cmd(SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Init
**功能 : 初始化 MPU9255
**輸入 : None
**輸出 : Status
**使用 : Status = MPU9255_Init();
**====================================================================================================*/
/*====================================================================================================*/
#define MPU9255_InitRegNum 13
void MPU9255_Init( MPU_InitTypeDef *MPUx )
{
  uint8_t MPU6555_InitData[MPU9255_InitRegNum][2] = {
    {0x10, MPU6555_USER_CTRL},      // 
    {0x00, MPU6555_PWR_MGMT_1},     // 
    {0x00, MPU6555_PWR_MGMT_2},     // Enable Acc & Gyro
    {0x07, MPU6555_CONFIG},         // DLPF_CFG[2:0] = 111;
    {0x18, MPU6555_GYRO_CONFIG},    // +-2000dps
    {0x08, MPU6555_ACCEL_CONFIG},   // +-4G
    {0x48, MPU6555_ACCEL_CONFIG_2}, // Set Acc Data Rates
    {0x30, MPU6555_INT_PIN_CFG},    // 
    {0x4D, MPU6555_I2C_MST_CTRL},   // I2C Speed 400 kHz

    // Set Slave to Read AK8963
    {0x8C, MPU6555_I2C_SLV0_ADDR},  // AK8963_I2C_ADDR ( 7'b000_1100 )
    {0x00, MPU6555_I2C_SLV0_REG},   // AK8963_WIA ( 0x00 )
    {0x81, MPU6555_I2C_SLV0_CTRL},  // Enable
    {0x01, MPU6555_I2C_MST_DELAY_CTRL}
  };

  MPU6555_InitData[4][0] = MPUx->MPU_Gyr_FullScale;       // MPU6500_GYRO_CONFIG
  MPU6555_InitData[3][0] = MPUx->MPU_Gyr_LowPassFilter;   // MPU6500_CONFIG
  MPU6555_InitData[5][0] = MPUx->MPU_Acc_FullScale;       // MPU6500_ACCEL_CONFIG
  MPU6555_InitData[6][0] = MPUx->MPU_Acc_LowPassFilter;   // MPU6500_ACCEL_CONFIG_2

  for(uint8_t i = 0; i < MPU9255_InitRegNum; i++) {
    MPU9255_WriteReg(MPU6555_InitData[i][1], MPU6555_InitData[i][0]);
    Delay_1ms(1);
  }

//  while(MPU9255_Check() != SUCCESS);
//  MPU9255_SetSpeed(SPIx_SPEED_HIGH);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_Check
**功能 : MPU9255 Check
**輸入 : None
**輸出 : Status
**使用 : Status = MPU9255_Check();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t MPU9255_Check( void )
{
	uint8_t DeviceID = 0x00;

  /* MPU6555 */
  DeviceID = 0x00;
  MPU9255_ReadReg(MPU6555_WHO_AM_I, &DeviceID);
  if(DeviceID != MPU6555_Device_ID)
    return ERROR;

//  /* AK8963 */
//  MPU9255_WriteReg(MPU6555_I2C_SLV0_ADDR, 0x8C);          // Set AK8963_I2C_ADDR = 7'b000_1100
//  Delay_1us(10);
//  MPU9255_WriteReg(MPU6555_I2C_SLV0_REG, AK8963_WIA);     // Set Write Reg
//  MPU9255_WriteReg(MPU6555_I2C_SLV0_CTRL, 0x81);          // Start Read
//  Delay_1ms(1);
//  MPU9255_ReadReg(MPU6555_EXT_SENS_DATA_00, &DeviceID);   // Read Data
//  if(DeviceID != AK8963_Device_ID)
//    return ERROR;

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : MPU9255_GetData
**功能 : 讀取感測器資料
**輸入 : *ReadBuf
**輸出 : None
**使用 : MPU9255_GetData(ReadBuf);
**====================================================================================================*/
/*====================================================================================================*/
void MPU9255_GetData( uint8_t *ReadBuf )
{
  MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, ReadBuf, 14);
}
/*==============================================================================================*/
/*==============================================================================================*/
