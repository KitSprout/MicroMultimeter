/* #include "stm32f1_flash.h" */

#ifndef __STM32F1_FLASH_H
#define __STM32F1_FLASH_H

#include "stm32f10x.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
// Medium Density ... STM32F103x8(64KB), STM32F103xB(128KB)
#define FLASH_START_ADDR        ((uint32_t)0x08000000)
#define FLASH_PAGE_SIZE         ((uint16_t)0x0400)   // 1KBytes
#define FLASH_PAGE_ADDR(PAGE)   ((uint32_t)(FLASH_START_ADDR + FLASH_PAGE_SIZE*(PAGE)))
/*=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8( uint32_t WritePage, const uint8_t *WriteData, uint16_t DataLen );
void Flash_WritePageU16( uint32_t WritePage, const uint16_t *WriteData, uint16_t DataLen );
void Flash_WritePageU32( uint32_t WritePage, const uint32_t *WriteData, uint16_t DataLen );
void Flash_ReadPageU8( uint32_t ReadPage, uint8_t *ReadData, uint16_t DataLen );
void Flash_ReadPageU16( uint32_t ReadPage, uint16_t *ReadData, uint16_t DataLen );
void Flash_ReadPageU32( uint32_t ReadPage, uint32_t *ReadData, uint16_t DataLen );
void Flash_ErasePage( uint32_t ErasePage );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif	 
