/* #include "module_ad5292.h" */

#ifndef __MODULE_AD5292_H
#define __MODULE_AD5292_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define AD5292_CMD_NOP            ((uint16_t)0x0000)  // NOP command: do nothing.
#define AD5292_CMD_WRITE_RDAC     ((uint16_t)0x0400)  // Write contents of serial data to RDAC.
#define AD5292_CMD_READ_RDAC      ((uint16_t)0x0800)  // Read RDAC wiper setting from the SDO output in the next frame.
#define AD5292_CMD_STORE_20TP     ((uint16_t)0x0C00)  // Store wiper setting: store RDAC setting to 20-TP memory.
#define AD5292_CMD_RST_20TP       ((uint16_t)0x1000)  // Reset: refresh RDAC with 20-TP stored value.
#define AD5292_CMD_READ_20TP      ((uint16_t)0x1400)  // Read contents of 20-TP memory, or status of 20-TP memory, from the SDO output in the next frame.
#define AD5292_CMD_WRITE_CTRL     ((uint16_t)0x1800)  // Write contents of serial data to control register.
#define AD5292_CMD_READ_CTRL      ((uint16_t)0x1C00)  // Read control register from the SDO output in the next frame.
#define AD5292_CMD_SET_MODE       ((uint16_t)0x2000)  // Software shutdown. D0 = 0 (normal mode). D0 = 1 (device placed in shutdown mode).

#define AD5292_CTRL_20TP_ENABLE   ((uint16_t)0x0001)  // 20-TP program enable, 0 = 20-TP program disabled (default), 1 = enable device for 20-TP program
#define AD5292_CTRL_RDAC_UPDATE   ((uint16_t)0x0002)  // RDAC register write protect, 0 = wiper position frozen to value in memory, 1 = allow update of wiper position through digital Interface
#define AD5292_CTRL_CALIB_ENABLE  ((uint16_t)0x0002)  // Calibration enable, 0 = resistor performance mode enabled (default), 1 = normal mode enabled
#define AD5292_CTRL_20TP_PROGRAM  ((uint16_t)0x0003)  // 20-TP memory program success, 0 = fuse program command unsuccessful (default), 1 = fuse program command successful
/*====================================================================================================*/
/*====================================================================================================*/
void AD5292_Config( void );
void AD5292_Init( void );
void AD5292_WriteRDAC( uint16_t WriteData );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
