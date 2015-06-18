/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_usb.h"
#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "module_ssd1331.h"
#include "module_mpu9255.h"

#include "exp_imu.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ExpIMU_Init
**功能 : DigiPower Config
**輸入 : None
**輸出 : None
**使用 : ExpIMU_Init();
**====================================================================================================*/
/*====================================================================================================*/
void ExpIMU_Init( void )
{
  MPU_InitTypeDef MPU_InitStruct;

  MPU9255_Config();

  MPU_InitStruct.MPU_Gyr_FullScale     = MPU_GyrFS_2000dps;
  MPU_InitStruct.MPU_Gyr_LowPassFilter = MPU_GyrLPS_41Hz;
  MPU_InitStruct.MPU_Acc_FullScale     = MPU_AccFS_4g;
  MPU_InitStruct.MPU_Acc_LowPassFilter = MPU_AccLPS_42Hz;
  MPU9255_Init(&MPU_InitStruct);

  if(ExpIMU_getDeviceID() != MPU6555_Device_ID) {
    OLED_DrawRectangleFill(0, 0, 11, 11, RED);
    return;
  }
  else {
    MPU9255_SetSpeed(SPI_BaudRatePrescaler_4);
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ExpROT_getRPM
**功能 : DigiPower Set Vol
**輸入 : None
**輸出 : None
**使用 : ExpROT_getRPM();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t ExpIMU_getDeviceID( void )
{
  uint8_t DeviceID = 0x00;

  DeviceID = 0x00;
  MPU9255_ReadReg(MPU6555_WHO_AM_I, &DeviceID);

  return DeviceID;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ExpROT_getRPM
**功能 : DigiPower Set Vol
**輸入 : None
**輸出 : None
**使用 : ExpROT_getRPM();
**====================================================================================================*/
/*====================================================================================================*/
void ExpIMU_getData( int16_t *dataIMU )
{
  uint8_t tmpRead[16] = {0};

  MPU9255_ReadRegs(MPU6555_ACCEL_XOUT_H, tmpRead, 14);

  dataIMU[0] = (Byte16(int16_t, tmpRead[0],  tmpRead[1]));  // Acc.X
  dataIMU[1] = (Byte16(int16_t, tmpRead[2],  tmpRead[3]));  // Acc.Y
  dataIMU[2] = (Byte16(int16_t, tmpRead[4],  tmpRead[5]));  // Acc.Z
  dataIMU[3] = (Byte16(int16_t, tmpRead[8],  tmpRead[9]));  // Gyr.X
  dataIMU[4] = (Byte16(int16_t, tmpRead[10], tmpRead[11])); // Gyr.Y
  dataIMU[5] = (Byte16(int16_t, tmpRead[12], tmpRead[13])); // Gyr.Z
  dataIMU[6] = (Byte16(int16_t, tmpRead[6],  tmpRead[7]));  // Temp
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : modeEXP_IMU
**功能 : 
**輸入 : None
**輸出 : None
**使用 : modeEXP_IMU();
**====================================================================================================*/
/*====================================================================================================*/
void modeEXP_IMU( void )
{
  uint8_t DeviceID = ExpIMU_getDeviceID();
  int16_t dataIMU[8] = {0};
  int16_t tmpData[8] = {0};

  if(DeviceID != MPU6555_Device_ID) {
    OLED_DrawRectangleFill(0, 0, 11, 11, RED);
    return;
  }
  else {
    OLED_DrawRectangleFill(0, 0, 11, 11, GREEN);
  }

  ExpIMU_getData(dataIMU);
  tmpData[0] = dataIMU[0] * IMU_ACC_4g * 1000;
  tmpData[1] = dataIMU[1] * IMU_ACC_4g * 1000;
  tmpData[2] = dataIMU[2] * IMU_ACC_4g * 1000;
  tmpData[3] = dataIMU[3] * IMU_GYR_2000dps * 10;
  tmpData[4] = dataIMU[4] * IMU_GYR_2000dps * 10;
  tmpData[5] = dataIMU[5] * IMU_GYR_2000dps * 10;

  OLED_PutNum_5x7(2, 13 + 9*0, Type_I, 5, tmpData[0], WHITE, BLACK);
  OLED_PutNum_5x7(2, 13 + 9*1, Type_I, 5, tmpData[1], WHITE, BLACK);
  OLED_PutNum_5x7(2, 13 + 9*2, Type_I, 5, tmpData[2], WHITE, BLACK);

  OLED_PutNum_5x7(2 + 48, 13 + 9*0, Type_I, 5, tmpData[3], WHITE, BLACK);
  OLED_PutNum_5x7(2 + 48, 13 + 9*1, Type_I, 5, tmpData[4], WHITE, BLACK);
  OLED_PutNum_5x7(2 + 48, 13 + 9*2, Type_I, 5, tmpData[5], WHITE, BLACK);

  USB_VCP_SendStr((uint8_t *)"Acc.X = ");   USB_VCP_SendNum(Type_I, 5, tmpData[0]);   USB_VCP_SendStr((uint8_t *)" mg\r\n");
//  USB_VCP_SendStr((uint8_t *)"Acc.Y = ");   USB_VCP_SendNum(Type_I, 5, tmpData[1]);   USB_VCP_SendStr((uint8_t *)" mg\r\n");
//  USB_VCP_SendStr((uint8_t *)"Acc.Z = ");   USB_VCP_SendNum(Type_I, 5, tmpData[2]);   USB_VCP_SendStr((uint8_t *)" mg\r\n");
//  USB_VCP_SendStr((uint8_t *)"Gyr.X = ");   USB_VCP_SendNum(Type_I, 5, tmpData[3]);   USB_VCP_SendStr((uint8_t *)" md\r\n");
//  USB_VCP_SendStr((uint8_t *)"Gyr.Y = ");   USB_VCP_SendNum(Type_I, 5, tmpData[4]);   USB_VCP_SendStr((uint8_t *)" md\r\n");
//  USB_VCP_SendStr((uint8_t *)"Gyr.Z = ");   USB_VCP_SendNum(Type_I, 5, tmpData[5]);   USB_VCP_SendStr((uint8_t *)" md\r\n");
}
/*=====================================================================================================*/
/*=====================================================================================================*/
