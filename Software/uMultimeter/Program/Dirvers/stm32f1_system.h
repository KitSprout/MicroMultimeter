/* #include "stm32f1_system.h" */

#ifndef __STM32F1_SYSTEM_H
#define __STM32F1_SYSTEM_H

#include "stm32f10x.h"
#include "stm32f1_delay.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define Bit_Band(Addr, BitNum)  ((Addr & 0xF0000000)+0x2000000+((Addr &0xFFFFF)<<5)+(BitNum<<2))
#define Mem_Addr(Addr)          *((__IO uint16_t*)(Addr))
#define Bit_Addr(Addr, BitNum)  Mem_Addr(Bit_Band(Addr, BitNum))

#define GPIOA_ODR_Addr  (GPIOA_BASE+12)
#define GPIOB_ODR_Addr  (GPIOB_BASE+12)
#define GPIOC_ODR_Addr  (GPIOC_BASE+12)
#define GPIOD_ODR_Addr  (GPIOD_BASE+12)
#define GPIOE_ODR_Addr  (GPIOE_BASE+12)
#define GPIOF_ODR_Addr  (GPIOF_BASE+12)
#define GPIOG_ODR_Addr  (GPIOG_BASE+12)
#define GPIOA_IDR_Addr  (GPIOA_BASE+8)
#define GPIOB_IDR_Addr  (GPIOB_BASE+8)
#define GPIOC_IDR_Addr  (GPIOC_BASE+8)
#define GPIOD_IDR_Addr  (GPIOD_BASE+8)
#define GPIOE_IDR_Addr  (GPIOE_BASE+8)
#define GPIOF_IDR_Addr  (GPIOF_BASE+8)
#define GPIOG_IDR_Addr  (GPIOG_BASE+8)

#define PAO(Pin)  Bit_Addr(GPIOA_ODR_Addr, Pin)
#define PAI(Pin)  Bit_Addr(GPIOA_IDR_Addr, Pin)
#define PBO(Pin)  Bit_Addr(GPIOB_ODR_Addr, Pin)
#define PBI(Pin)  Bit_Addr(GPIOB_IDR_Addr, Pin)
#define PCO(Pin)  Bit_Addr(GPIOC_ODR_Addr, Pin)
#define PCI(Pin)  Bit_Addr(GPIOC_IDR_Addr, Pin)
#define PDO(Pin)  Bit_Addr(GPIOD_ODR_Addr, Pin)
#define PDI(Pin)  Bit_Addr(GPIOD_IDR_Addr, Pin)
#define PEO(Pin)  Bit_Addr(GPIOE_ODR_Addr, Pin)
#define PEI(Pin)  Bit_Addr(GPIOE_IDR_Addr, Pin)
#define PFO(Pin)  Bit_Addr(GPIOF_ODR_Addr, Pin)
#define PFI(Pin)  Bit_Addr(GPIOF_IDR_Addr, Pin)
#define PGO(Pin)  Bit_Addr(GPIOG_ODR_Addr, Pin)
#define PGI(Pin)  Bit_Addr(GPIOG_IDR_Addr, Pin)
/*====================================================================================================*/
/*====================================================================================================*/
#define _GPIO_SET(_PORT, _PIN)    (_PORT->BSRR = _PIN)
#define _GPIO_RST(_PORT, _PIN)    (_PORT->BRR  = _PIN)
#define _GPIO_TOG(_PORT, _PIN)    (_PORT->ODR ^= _PIN)
#define _GPIO_READ(_PORT, _PIN)   (_PORT->IDR  & _PIN)
/*====================================================================================================*/
/*====================================================================================================*/
#define U8_MAX  ((uint8_t)255)
#define S8_MAX  ((int8_t)127)
#define S8_MIN  ((int8_t)-128)
#define U16_MAX ((uint16_t)65535u)
#define S16_MAX ((int16_t)32767)
#define S16_MIN ((int16_t)-32768)
#define U32_MAX ((uint32_t)4294967295uL)
#define S32_MAX ((int32_t)2147483647)
#define S32_MIN ((int32_t)-2147483648)

#define Byte32(Type, Byte4, Byte3, Byte2, Byte1)  ((Type)((((uint8_t)(Byte4))<<24) | (((uint8_t)(Byte3))<<16) | (((uint8_t)(Byte2))<<8) | ((uint8_t)(Byte1))))
#define Byte32U16H(Byte32U16) ((uint16_t)( Byte32U16&0xFFFF0000)>>16)
#define Byte32U16L(Byte32U16) ((uint16_t)((Byte32U16&0x0000FFFF)))
#define Byte32U8_1(Byte32U8)  ((uint8_t)( Byte32U8&0x000000FF))
#define Byte32U8_2(Byte32U8)  ((uint8_t)((Byte32U8&0x0000FF00)>>8))
#define Byte32U8_3(Byte32U8)  ((uint8_t)((Byte32U8&0x00FF0000)>>16))
#define Byte32U8_4(Byte32U8)  ((uint8_t)((Byte32U8&0xFF000000)>>24))

#define Byte16(Type, ByteH, ByteL)  ((Type)((((uint16_t)(ByteH))<<8) | ((uint16_t)(ByteL))))
#define Byte16U8H(Byte32U8) ((uint8_t)( Byte32U8&0xFF00)>>8)
#define Byte16U8L(Byte32U8) ((uint8_t)((Byte32U8&0x00FF)))

#define Byte8H(ByteH) ((uint8_t)(((uint16_t)(ByteH))>>8))
#define Byte8L(ByteL) ((uint8_t)(ByteL))

#define NULL 0
/*====================================================================================================*/
/*====================================================================================================*/
#endif
