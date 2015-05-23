/* #include "stm32f0_usart.h" */

#ifndef __STM32F1_USART_H
#define __STM32F1_USART_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
void   UART_SendByte( USART_TypeDef *USARTx, int8_t *SendData );
void   UART_RecvByte( USART_TypeDef *USARTx, int8_t *RecvData );
int8_t UART_RecvByteWTO( USART_TypeDef *USARTx, int8_t *RecvData, int32_t TimeoutMs );
void   UART_SendData( USART_TypeDef *USARTx, int8_t *SendData, uint16_t DataLen );
void   UART_RecvData( USART_TypeDef *USARTx, int8_t *RecvData, uint16_t DataLen );
int8_t UART_RecvDataWTO( USART_TypeDef *USARTx, int8_t *RecvData, uint16_t DataLen, int32_t TimeoutMs );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
