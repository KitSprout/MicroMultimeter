/* #include "module_rs232.h" */

#ifndef __MODULE_RS232_H
#define __MODULE_RS232_H

#include "stm32f10x.h"
#include "algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
void   RS232_Config( void );
void   RS232_SendStr( int8_t *pWord );
void   RS232_SendNum( StrType Type, uint8_t NumLen, int32_t SendData );
void   RS232_SendData( int8_t *SendData, uint16_t DataLen );
void   RS232_RecvStr( int8_t *pWord );
int8_t RS232_RecvStrWTO( int8_t *pWord, int32_t TimeoutMs );
void   RS232_RecvData( int8_t *RecvData, uint16_t DataLen );
int8_t RS232_RecvDataWTO( int8_t *RecvData, uint16_t DataLen, int32_t TimeoutMs );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
