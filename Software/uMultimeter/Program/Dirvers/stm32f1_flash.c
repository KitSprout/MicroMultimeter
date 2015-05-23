/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_flash.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU8
**功能 : U8 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU8(FLASH_PAGE_ADDR(12), WriteData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU8( uint32_t WritePage, const uint8_t *WriteData, uint16_t DataLen )
{
  uint16_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();

  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WritePage);
  while((Count < DataLen) && (FLASHStatus == FLASH_COMPLETE)) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage + Count, Byte16(uint16_t, WriteData[Count], WriteData[Count+1]));
    Count += 2;
  }
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU16
**功能 : U16 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU16(FLASH_PAGE_ADDR(12), WriteData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU16( uint32_t WritePage, const uint16_t *WriteData, uint16_t DataLen )
{
  uint16_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();

  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WritePage);
  while((Count < DataLen) && (FLASHStatus == FLASH_COMPLETE)) {
    FLASHStatus = FLASH_ProgramHalfWord(WritePage + (Count << 1), WriteData[Count]);
    Count++;
  }
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_WritePageU32
**功能 : U32 寫入 FLASH
**輸入 : WritePage, *WriteData, DataLen
**輸出 : None
**使用 : Flash_WritePageU32(FLASH_PAGE_ADDR(12), WriteData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_WritePageU32( uint32_t WritePage, const uint32_t *WriteData, uint16_t DataLen )
{
  uint16_t Count = 0;
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();

  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(WritePage);
  while((Count < DataLen) && (FLASHStatus == FLASH_COMPLETE)) {
    FLASHStatus = FLASH_ProgramWord(WritePage + (Count << 2), WriteData[Count]);
    Count++;
  }
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU8
**功能 : U8 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU8(FLASH_PAGE_ADDR(12), ReadData, 1024);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU8( uint32_t ReadPage, uint8_t *ReadData, uint16_t DataLen )
{
  uint16_t Count = 0;
  uint16_t ReadBuf = 0;

  while(Count < DataLen) {
    ReadBuf = (uint16_t)(*(volatile uint32_t*)(ReadPage + Count));
    ReadData[Count++] = Byte8H(ReadBuf);
    ReadData[Count++] = Byte8L(ReadBuf);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU16
**功能 : U16 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU16(FLASH_PAGE_ADDR(12), ReadData, 512);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU16( uint32_t ReadPage, uint16_t *ReadData, uint16_t DataLen )
{
  uint16_t Count = 0;

  while(Count < DataLen) {
    ReadData[Count] = (uint16_t)(*(volatile uint32_t*)(ReadPage + (Count << 1)));
    Count++;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ReadPageU32
**功能 : U32 讀取 FLASH
**輸入 : ReadPage, *ReadData, DataLen
**輸出 : None
**使用 : Flash_ReadPageU32(FLASH_PAGE_ADDR(12), ReadData, 256);
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ReadPageU32( uint32_t ReadPage, uint32_t *ReadData, uint16_t DataLen )
{
  uint16_t Count = 0;

  while(Count < DataLen) {
    ReadData[Count] = (uint32_t)(*(volatile uint32_t*)(ReadPage + (Count << 2)));
    Count++;
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : Flash_ErasePage
**功能 : 擦除 FLASH
**輸入 : ErasePage
**輸出 : None
**使用 : Flash_ErasePage(FLASH_PAGE_ADDR(12));
**=====================================================================================================*/
/*=====================================================================================================*/
void Flash_ErasePage( uint32_t ErasePage )
{
  FLASH_Status FLASHStatus;

  FLASH_UnlockBank1();
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
  FLASHStatus = FLASH_ErasePage(ErasePage);
  while(FLASHStatus != FLASH_COMPLETE);
  FLASH_LockBank1();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
