/* #include "algorithm_compare.h" */

#ifndef __ALGORITHM_COMPARE_H
#define __ALGORITHM_COMPARE_H

#include "stm32f10x.h"
/*====================================================================================================*/
/*====================================================================================================*/
uint8_t Cmp_ArrU8( const uint8_t *Arr1, const uint8_t *Arr2, uint32_t dataLen );
uint8_t Cmp_ArrU16( const uint16_t *Arr1, const uint16_t *Arr2, uint32_t dataLen );
uint8_t Cmp_ArrU32( const uint32_t *Arr1, const uint32_t *Arr2, uint32_t DataLen );
uint8_t Cmp_ArrU8U16( const uint8_t *Arr1, const uint16_t *Arr2, uint32_t dataLen );
/*====================================================================================================*/
/*====================================================================================================*/
#endif
