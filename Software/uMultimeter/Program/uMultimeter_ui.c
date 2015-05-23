/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "module_ssd1331.h"
#include "module_buzzer.h"
#include "uMultimeter_measure.h"

#include "api_waveForm.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : getNumDigit
**功能 : Get Digit in Number
**輸入 : numBuf, newNum
**輸出 : length
**使用 : getNumDigit();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t getNumDigit( uint8_t *numBuf, uint32_t newNum )
{
  uint8_t i = 0, length = 0;

  while(newNum != 0) {
    numBuf[i++] = newNum % 10;
    newNum = newNum / 10;
    length++;
  }

  return length;
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint16_t UI_charArray_V5x16_CH1[5] = {0x3A58,0x4249,0x43C8,0x4249,0x3A5C}; // CH1:
const uint16_t UI_charArray_V5x16_CH2[5] = {0x3A5C,0x4245,0x43DC,0x4251,0x3A5C}; // CH2:
const uint16_t UI_charArray_V5x9_DC[5]   = {0x01C7,0x0128,0x0128,0x0128,0x01C7}; // DC
const uint16_t UI_charArray_V5x9_AC[5]   = {0x00C7,0x0128,0x0128,0x01E8,0x0127}; // AC
const uint16_t UI_charArray_V16x16_m[22] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCE3C,0xFF7E,0xE3C7,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183};  // 16x16 m
const uint16_t UI_charArray_V16x16_V[22] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xE01C,0xE01C,0x6038,0x7038,0x7030,0x3070,0x3870,0x3860,0x18E0,0x18E0,0x1CC0,0x0DC0,0x0D80,0x0D80,0x0780,0x0700};  // 16x16 V

void uMultimeterUI_modeVOL_putNum5x3( uint8_t CoordiX, uint8_t CoordiY, uint16_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[4] = {0};

  getNumDigit(num, NumData);

  for(int8_t i = 0; i < 4; i++)
    OLED_PutChar(CoordiX + i*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3-i]], FontColor, BackColor);
}
void uMultimeterUI_modeVOL_putBigNum16x16( uint8_t CoordiX, uint8_t CoordiY, uint16_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[5] = {0};

  if(NumData < 1000) {
    getNumDigit(num, NumData);
    if(num[2] == 0)
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], FontColor, BackColor);
    if((num[2] == 0) && (num[1] == 0))
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[1]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[1]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[0]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 51, CoordiY, 22, 16, UI_charArray_V16x16_m, FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_V16x16_V, FontColor, BackColor);
  }
  else if((NumData >= 1000) && (NumData < 10000)) {
    if(NumData%10 < 5)
      getNumDigit(num, NumData);
    else
      getNumDigit(num, NumData+5);
    OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[3]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[10], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 3*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[1]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_V16x16_V, FontColor, BackColor);
  }
  else {
    if(NumData%100 < 50)
      getNumDigit(num, NumData);
    else
      getNumDigit(num, NumData+50);
    OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[4]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[3]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[10], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 3*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_V16x16_V, FontColor, BackColor);
  }
}

#define MODE_VOL_CH1_X    0
#define MODE_VOL_CH1_Y    0
#define MODE_VOL_NUM1_X   MODE_VOL_CH1_X + 18
#define MODE_VOL_NUM1_Y   MODE_VOL_CH1_Y

#define MODE_VOL_CH2_X    MODE_VOL_CH1_X + 40
#define MODE_VOL_CH2_Y    MODE_VOL_CH1_Y
#define MODE_VOL_NUM2_X   MODE_VOL_CH2_X + 18
#define MODE_VOL_NUM2_Y   MODE_VOL_CH2_Y

#define MODE_VOL_DCAC_X   82
#define MODE_VOL_DCAC_Y   MODE_VOL_CH1_Y

#define MODE_VOL_BIGN_X   7
#define MODE_VOL_BIGN_Y   22
void uMultimeterUI_modeVOL_setMode( uint8_t mode )
{
  if(!mode) OLED_PutChar16(MODE_VOL_DCAC_X, MODE_VOL_DCAC_Y, 5, 9, UI_charArray_V5x9_DC, WHITE, BLACK);
  else      OLED_PutChar16(MODE_VOL_DCAC_X, MODE_VOL_DCAC_Y, 5, 9, UI_charArray_V5x9_AC, WHITE, BLACK);
}
void uMultimeterUI_modeVOL_Init( uM_modeS modeS )
{
  OLED_DrawRectangleFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  OLED_PutChar16(MODE_VOL_CH1_X, MODE_VOL_CH1_Y, 5, 16, UI_charArray_V5x16_CH1, GREEN, BLACK);
  OLED_PutChar16(MODE_VOL_CH2_X, MODE_VOL_CH2_Y, 5, 16, UI_charArray_V5x16_CH2,  BLUE, BLACK);
  uMultimeterUI_modeVOL_setMode(0);
  uMultimeterUI_modeVOL(modeS, 0, 0, 0);
}
void uMultimeterUI_modeVOL( uM_modeS modeS, uint16_t NumCH1, uint16_t NumCH2, uint16_t BigNum )
{
  static uint16_t tmpData = 0;
  uint16_t deltaData = 0;

  uMultimeterUI_modeVOL_putNum5x3(MODE_VOL_NUM1_X, MODE_VOL_NUM1_Y, NumCH1, WHITE, BLACK);
  uMultimeterUI_modeVOL_putNum5x3(MODE_VOL_NUM2_X, MODE_VOL_NUM2_Y, NumCH2, WHITE, BLACK);

  deltaData = (BigNum > tmpData) ? BigNum - tmpData : tmpData - BigNum;
  if(deltaData > 40) {  // delat > 40 mV
    OLED_DrawRectangleFill(MODE_VOL_DCAC_X + 12, MODE_VOL_DCAC_Y, 2, 5, RED);
    tmpData = BigNum;
  }
  else
    OLED_DrawRectangleFill(MODE_VOL_DCAC_X + 12, MODE_VOL_DCAC_Y, 2, 5, BLACK);

  uMultimeterUI_modeVOL_putBigNum16x16(MODE_VOL_BIGN_X, MODE_VOL_BIGN_Y, BigNum, WHITE, BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint16_t UI_charArray_R5x16_BEEP[5] = {0xE777,0x9445,0xE667,0x9444,0xE774}; // BEEP
const uint16_t UI_charArray_R5x16_DIO[5]  = {0x0460,0x05E0,0x7FFE,0x05E0,0x0460}; // DIODE
const uint16_t UI_charArray_R5x16_RES[5]  = {0x0FF0,0x0FF0,0x7FFE,0x0FF0,0x0FF0}; // RES
const uint32_t UI_charArray_R5x21_CODE[5] = {0x000E6738,0x001094A2,0x001094B0,0x001094A2,0x000E6738}; // CODE:
const uint16_t UI_charArray_R16x16_K[22]  = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xC070,0xC0E0,0xC1C0,0xC380,0xC700,0xCE00,0xDC00,0xF800,0xFC00,0xCE00,0xC700,0xC380,0xC1C0,0xC0E0,0xC070,0xC078};  // 16x16 m
const uint16_t UI_charArray_R16x16_R[22]  = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFF80,0xFFC0,0xC1E0,0xC0E0,0xC0E0,0xC0E0,0xC1C0,0xFF80,0xFF00,0xC780,0xC380,0xC1C0,0xC0E0,0xC060,0xC070,0xC038};  // 16x16 V

void uMultimeterUI_modeRES_putCodeNum5x3( uint8_t CoordiX, uint8_t CoordiY, uint32_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[7] = {0};
  uint8_t length = 0;

  length = getNumDigit(num, NumData);

  if(NumData == 0) {
    OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
  }
  else if(length == 1) {
    OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[0]], WHITE, BLACK);
    OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
  }
  else {
    OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[length-1]], WHITE, BLACK);
    OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[length-2]], WHITE, BLACK);
    OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[length-2], WHITE, BLACK);
  }
}

void uMultimeterUI_modeRES_putBigNum16x16( uint8_t CoordiX, uint8_t CoordiY, uint32_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[7] = {0};

  getNumDigit(num, NumData);

  if(NumData < 1000) {
    OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[0], BackColor, BackColor);
    if(num[2] == 0)
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], FontColor, BackColor);
    if((num[2] == 0) && (num[1] == 0))
      OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[1]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[1]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 3*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[0]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_R16x16_R, FontColor, BackColor);
  }
  else if((NumData >= 1000) && (NumData < 100000)) {
    if(num[4] == 0)
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[4]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[4]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[3]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[10],     FontColor, BackColor);
    OLED_PutChar16(CoordiX + 3*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[2]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_R16x16_K, FontColor, BackColor);
  }
  else {
    if(num[6] == 0)
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[6]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 0*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[6]], FontColor, BackColor);
    if((num[6] == 0) && (num[5] == 0))
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[5]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 1*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[5]], FontColor, BackColor);
    if((num[6] == 0) && (num[5] == 0) && (num[4] == 0))
      OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[4]], BackColor, BackColor);
    else
      OLED_PutChar16(CoordiX + 2*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[4]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 3*17, CoordiY, 22, 16, ASCII_NUM_22x16[num[3]], FontColor, BackColor);
    OLED_PutChar16(CoordiX + 72, CoordiY, 22, 16, UI_charArray_R16x16_K, FontColor, BackColor);
  }
}

#define MODE_RES_BEEP_X   0
#define MODE_RES_BEEP_Y   0

#define MODE_RES_MODE_X   20
#define MODE_RES_MODE_Y   MODE_RES_BEEP_Y

#define MODE_RES_CODE_X   61
#define MODE_RES_CODE_Y   MODE_RES_BEEP_Y

#define MODE_RES_BIGN_X   7
#define MODE_RES_BIGN_Y   22

void uMultimeterUI_modeRES_setBeep( uint8_t mode )
{
  uint16_t tmpMode = (mode) ? YELLOW : WHITE;

  OLED_PutChar16(MODE_RES_BEEP_X, MODE_RES_BEEP_Y, 5, 16, UI_charArray_R5x16_BEEP, tmpMode, BLACK);
}
void uMultimeterUI_modeRES_setMode( uM_modeS modeS )
{
  if(modeS == MODES_RES_DIO) {
    OLED_PutChar16(MODE_RES_MODE_X + 0*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_DIO,  BLUE, BLACK);
    OLED_PutChar16(MODE_RES_MODE_X + 1*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_RES, BLACK, BLACK);
  }
  else {
    OLED_PutChar16(MODE_RES_MODE_X + 0*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_DIO, BLACK, BLACK);
    OLED_PutChar16(MODE_RES_MODE_X + 1*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_RES, GREEN, BLACK);
  }
}
void uMultimeterUI_modeRES_Init( uM_modeS modeS )
{
  OLED_DrawRectangleFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  OLED_PutChar32(MODE_RES_CODE_X, MODE_RES_CODE_Y, 5, 21, UI_charArray_R5x21_CODE, WHITE, BLACK);

  uMultimeterUI_modeRES_setMode(modeS);
}
void uMultimeterUI_modeRES( uM_modeS modeS, uint32_t BigNum, uint8_t BeepState )
{
  uMultimeterUI_modeRES_setBeep(BeepState);
  uMultimeterUI_modeRES_setMode(modeS);

  switch(modeS) {
    case MODES_RES_RES:
      uMultimeterUI_modeRES_putCodeNum5x3(MODE_RES_CODE_X + 21, MODE_RES_CODE_Y, BigNum, WHITE, BLACK);
      uMultimeterUI_modeRES_putBigNum16x16(MODE_RES_BIGN_X, MODE_RES_BIGN_Y, BigNum, WHITE, BLACK);
      break;
    case MODES_RES_DIO:
      uMultimeterUI_modeRES_putCodeNum5x3(MODE_RES_CODE_X + 21, MODE_RES_CODE_Y, 0, WHITE, BLACK);
      uMultimeterUI_modeVOL_putBigNum16x16(MODE_RES_BIGN_X, MODE_RES_BIGN_Y, BigNum, WHITE, BLACK);
      break;
    default:
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint8_t  UI_charArray_P5x6_D[5]    = {0x38,0x25,0x24,0x25,0x38}; // D:
const uint8_t  UI_charArray_P5x6_F[5]    = {0x3C,0x21,0x38,0x21,0x20}; // F:
const uint8_t  UI_charArray_P5x6_P[5]    = {0x19,0x12,0x04,0x09,0x13}; // %
const uint16_t UI_charArray_P5x13_HZ[5]  = {0x0120,0x012F,0x01E2,0x0124,0x012F}; // HZ
const uint16_t UI_charArray_P5x13_KHZ[5] = {0x1120,0x112F,0x15E2,0x1924,0x152F}; // KHZ

void uMultimeterUI_modePWM_putDutyNum5x4( uint8_t CoordiX, uint8_t CoordiY, uint16_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t  num[5] = {0};

  getNumDigit(num, NumData);

  if(num[4] == 0)
    OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[4]], BackColor, BackColor);
  else
    OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[4]], FontColor, BackColor);
  if((num[4] == 0) && (num[3] == 0))
    OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3]], BackColor, BackColor);
  else
    OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3]], FontColor, BackColor);
  OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[2]], FontColor, BackColor);
  OLED_PutChar(CoordiX + 3*4, CoordiY, 5, 4, ASCII_NUM_5x3[10],     FontColor, BackColor);
  OLED_PutChar(CoordiX + 4*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[1]], FontColor, BackColor);
  OLED_PutChar(CoordiX + 5*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[0]], FontColor, BackColor);
}
void uMultimeterUI_modePWM_putFreqNum5x4( uint8_t CoordiX, uint8_t CoordiY, uint32_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[7] = {0};

  getNumDigit(num, NumData);

  if(NumData < 10000) {
    if(num[3] == 0)
      OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3]], FontColor, BackColor);
    if((num[3] == 0) && (num[2] == 0))
      OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[2]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[2]], FontColor, BackColor);
    if((num[3] == 0) && (num[2] == 0) && (num[1] == 0))
      OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[1]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[1]], FontColor, BackColor);
    OLED_PutChar(CoordiX + 3*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[0]], FontColor, BackColor);

    OLED_PutChar16(CoordiX + 18, CoordiY, 5, 13, UI_charArray_P5x13_HZ, FontColor, BackColor);
  }
  else {
    if(num[6] == 0)
      OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[6]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 0*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[6]], FontColor, BackColor);
    if((num[6] == 0) && (num[5] == 0))
      OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[5]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 1*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[5]], FontColor, BackColor);
    if((num[6] == 0) && (num[5] == 0) && (num[4] == 0))
      OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[4]], BackColor, BackColor);
    else
      OLED_PutChar(CoordiX + 2*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[4]], FontColor, BackColor);
    OLED_PutChar(CoordiX + 3*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3]], FontColor, BackColor);

    OLED_PutChar16(CoordiX + 18, CoordiY, 5, 13, UI_charArray_P5x13_KHZ, FontColor, BackColor);
  }
}

#define WAVE_H    32
#define WAVE_W    60
#define WAVE_X_W  8
#define WAVE_X_H  3
void uMultimeterUI_modePWM_putPLUSE( uint8_t CoordiX, uint8_t CoordiY, uint16_t Duty, uint16_t LineColor, uint16_t BackColor )
{
  static uint8_t OldDuty = 0;
  uint8_t NewDuty = Duty * 0.006f;  // 0 ~ 100.00% -> 0 ~ 60

  if(NewDuty == OldDuty) {
  
  }
  else if(NewDuty > OldDuty) {
    OLED_DrawRectangle(CoordiX + WAVE_X_W + OldDuty - 2, CoordiY, NewDuty - OldDuty + 1, WAVE_H, BackColor);
    OLED_DrawRectangleFill(CoordiX + WAVE_X_W + OldDuty - 1, CoordiY, NewDuty - OldDuty - 1, WAVE_X_H, BackColor);
  }
  else {
    OLED_DrawRectangle(CoordiX + WAVE_X_W + NewDuty - 2, CoordiY, OldDuty - NewDuty + 1, WAVE_H, BackColor);
    OLED_DrawRectangleFill(CoordiX + WAVE_X_W + NewDuty - 1, CoordiY + WAVE_H - WAVE_X_H, OldDuty - NewDuty - 1, WAVE_X_H, BackColor);
  }

  OLED_DrawRectangleFill(CoordiX,                          CoordiY + WAVE_H - WAVE_X_H, WAVE_X_W,             WAVE_X_H, LineColor);
  OLED_DrawRectangleFill(CoordiX + WAVE_X_W - 1,           CoordiY,                     NewDuty,              WAVE_X_H, LineColor);
  OLED_DrawRectangleFill(CoordiX + WAVE_X_W + NewDuty - 2, CoordiY + WAVE_H - WAVE_X_H, WAVE_W - NewDuty + 1, WAVE_X_H, LineColor);
  OLED_DrawRectangleFill(CoordiX + WAVE_X_W + WAVE_W - 2,  CoordiY,                     WAVE_X_W,             WAVE_X_H, LineColor);

  OLED_DrawLineY(CoordiX + WAVE_X_W - 1,           CoordiY, WAVE_H, LineColor);
  OLED_DrawLineY(CoordiX + WAVE_X_W + NewDuty - 2, CoordiY, WAVE_H, LineColor);
  OLED_DrawLineY(CoordiX + WAVE_X_W + WAVE_W - 2,  CoordiY, WAVE_H, LineColor);

  OldDuty = NewDuty;
}

#define MODE_PWM_DUTY_X   1
#define MODE_PWM_DUTY_Y   0
#define MODE_PWM_NUM1_X   MODE_PWM_DUTY_X + 6
#define MODE_PWM_NUM1_Y   MODE_PWM_DUTY_Y

#define MODE_PWM_FREQ_X   MODE_PWM_DUTY_X + 56
#define MODE_PWM_FREQ_Y   0
#define MODE_PWM_NUM2_X   MODE_PWM_FREQ_X + 6
#define MODE_PWM_NUM2_Y   MODE_PWM_FREQ_Y

#define MODE_PWM_PLUSE_X  12
#define MODE_PWM_PLUSE_Y  15

void uMultimeterUI_modePWM_Init( uM_modeS modeS )
{
  OLED_DrawRectangleFill(0, 0, OLED_W, OLED_H-9, BLACK);
  OLED_PutChar(MODE_PWM_DUTY_X, MODE_PWM_DUTY_Y, 5, 6, UI_charArray_P5x6_D, WHITE, BLACK);
  OLED_PutChar(MODE_PWM_DUTY_X + 31, MODE_PWM_DUTY_Y, 5, 6, UI_charArray_P5x6_P, WHITE, BLACK);
  OLED_PutChar(MODE_PWM_FREQ_X, MODE_PWM_FREQ_Y, 5, 6, UI_charArray_P5x6_F, WHITE, BLACK);
  uMultimeterUI_modePWM_putDutyNum5x4(MODE_PWM_NUM1_X, MODE_PWM_NUM1_Y, 0, WHITE, BLACK);
  uMultimeterUI_modePWM_putFreqNum5x4(MODE_PWM_NUM2_X, MODE_PWM_NUM2_Y, 0, WHITE, BLACK);
}
void uMultimeterUI_modePWM( uM_modeS modeS, uint16_t DutyData, uint32_t FreqData )
{
  uMultimeterUI_modePWM_putDutyNum5x4(MODE_PWM_NUM1_X, MODE_PWM_NUM1_Y, DutyData, WHITE, BLACK);
  uMultimeterUI_modePWM_putFreqNum5x4(MODE_PWM_NUM2_X, MODE_PWM_NUM2_Y, FreqData, WHITE, BLACK);
  uMultimeterUI_modePWM_putPLUSE(MODE_PWM_PLUSE_X, MODE_PWM_PLUSE_Y, DutyData, GREEN, BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeterUI_modeWAV_putNum5x3( uint8_t CoordiX, uint8_t CoordiY, uint16_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t num[4] = {0};

  getNumDigit(num, NumData);

  for(int8_t i = 0; i < 4; i++)
    OLED_PutChar(CoordiX + i*4, CoordiY, 5, 4, ASCII_NUM_5x3[num[3-i]], FontColor, BackColor);
}

#define MODE_WAV_CH1_X   2
#define MODE_WAV_CH1_Y   1
#define MODE_WAV_CH2_X   50
#define MODE_WAV_CH2_Y   MODE_WAV_CH1_Y

void uMultimeterUI_modeWAV_Init( uM_modeS modeS )
{
  OLED_DrawRectangleFill(0, 0, OLED_W, OLED_H-9, BLACK);
  OLED_DrawRectangleFill(0, 0, 96, 6, WHITE);
  OLED_DrawRectangleFill(MODE_WAV_CH1_X, MODE_WAV_CH1_Y, 16, 5, GREEN);
  OLED_DrawRectangleFill(MODE_WAV_CH2_X, MODE_WAV_CH1_Y, 16, 5, BLUE);
}
void uMultimeterUI_modeWAV( uM_modeS modeS, WaveForm_Struct *pWaveForm )
{
  uMultimeterUI_modeWAV_putNum5x3(MODE_WAV_CH1_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[0], BLACK, WHITE);
  uMultimeterUI_modeWAV_putNum5x3(MODE_WAV_CH2_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[1], BLACK, WHITE);

  switch(modeS) {
    case MODES_WAV_CH1:
      pWaveForm->PointColor[0] = BLACK;
      pWaveForm->PointColor[1] = GREEN;
      pWaveForm->Data[1] = pWaveForm->Data[0];
      break;
    case MODES_WAV_CH2:
      pWaveForm->PointColor[0] = BLACK;
      pWaveForm->PointColor[1] = BLUE;
      break;
    case MODES_WAV_ALL:
      pWaveForm->PointColor[0] = GREEN;
      pWaveForm->PointColor[1] = BLUE;
      break;
    default:
      break;
  }
  WaveFormPrint(pWaveForm, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
void uMultimeterUI_modeEXP_Init( uM_modeS modeS )
{
  OLED_DrawRectangleFill(0, 0, OLED_W, OLED_H-9, BLACK);

  // 數位電源, 類比訊號生, 數位電阻, 電流計, 溫度計, 高精度ADC, 轉速計, 慣性測量, 溼度, 磁力計, 回流悍, 數位麥克風
  // POW,      DAC,        POT,      CUR,    TEMP,   ADC,       ROT,    IMU,      MOI,  MAG,    RFLW,  MIC
  OLED_PutStr_5x7(4+30*0, 3+10*0, (int8_t*)"POW", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*0, 3+10*1, (int8_t*)"DAC", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*0, 3+10*2, (int8_t*)"POT", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*0, 3+10*3, (int8_t*)"CUR", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*0, 3+10*4, (int8_t*)"ADC", WHITE, BLACK);

  OLED_PutStr_5x7(4+30*1, 3+10*0, (int8_t*)"ROT", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*1, 3+10*1, (int8_t*)"IMU", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*1, 3+10*2, (int8_t*)"MOI", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*1, 3+10*3, (int8_t*)"MAG", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*1, 3+10*4, (int8_t*)"MIC", WHITE, BLACK);

  OLED_PutStr_5x7(4+30*2, 3+10*0, (int8_t*)"TEMP", WHITE, BLACK);
  OLED_PutStr_5x7(4+30*2, 3+10*1, (int8_t*)"RFLW", WHITE, BLACK);
}
void uMultimeterUI_modeEXP( uM_modeS modeS )
{

}
/*====================================================================================================*/
/*====================================================================================================*/
#define SEL_WINDOW_X 0
#define SEL_WINDOW_Y OLED_H-1-8

const uint16_t fontMatrix_5x16[12][5] = {
  {0x4990, 0x4A50, 0x4A50, 0x4A50, 0x319E}, // VOL, 0
  {0x7BCE, 0x4A10, 0x7B8C, 0x5202, 0x4BDC}, // RES, 1
  {0xF45B, 0x9455, 0xF555, 0x8551, 0x8291}, // PWM, 2
  {0x8992, 0x8A52, 0xAA52, 0xABD2, 0x524C}, // WAV, 3
  {0xF45E, 0x8292, 0xE11E, 0x8290, 0xF450}, // EXP, 4

  {0x1808, 0x241C, 0x2548, 0x2548, 0x19CC}, // OUT, 5
  {0x0700, 0x0200, 0x0270, 0x0250, 0x0750}, // IN,  6
  {0x3A58, 0x4248, 0x43C8, 0x4248, 0x3A5C}, // CH1, 7
  {0x3A5C, 0x4244, 0x43DC, 0x4250, 0x3A5C}, // CH2, 8
  {0x39DE, 0x2490, 0x249C, 0x2490, 0x39D0}, // DIF, 9
  {0x39CC, 0x2492, 0x2492, 0x2492, 0x39CC}, // DIO, 10
  {0x1910, 0x2510, 0x2510, 0x3D10, 0x25DC}, // ALL, 11
};

void uMultimeterUI_menuDisplay_button( uint8_t CoordiX, uint8_t CoordiY, uint8_t Select, uint16_t FontColor, uint16_t BackColor )
{
  OLED_PutChar16(CoordiX+1, CoordiY+1, 5, 16, fontMatrix_5x16[Select], FontColor, BackColor);
  OLED_DrawRectangle(CoordiX, CoordiY, 18, 7, BackColor);
}
void uMultimeterUI_menuDisplay( uM_mode mode, uM_modeS modeS )
{
  switch(mode) {
    case MODE_VOL:
      if(modeS == MODES_VOL_CH1)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 7, WHITE, BLACK);
      else if(modeS == MODES_VOL_CH2)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 8, WHITE, BLACK);
      else
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 9, WHITE, BLACK);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 1, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 2, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 3, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y+1, 4, BLACK, WHITE);
      break;
    case MODE_RES:
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 0, BLACK, WHITE);
      if(modeS == MODES_RES_RES)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 1, WHITE, BLACK);
      else
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 10, WHITE, BLACK);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 2, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 3, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y+1, 4, BLACK, WHITE);
      break;
    case MODE_PWM:
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 0, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 1, BLACK, WHITE);
      if(modeS == MODES_PWM_OUT)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 5, WHITE, BLACK);
      else
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 6, WHITE, BLACK);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 3, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y+1, 4, BLACK, WHITE);
      break;
    case MODE_WAV:
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 0, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 1, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 2, BLACK, WHITE);
      if(modeS == MODES_WAV_CH1)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 7, WHITE, BLACK);
      else if(modeS == MODES_WAV_CH2)
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 8, WHITE, BLACK);
      else
        uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 11, WHITE, BLACK);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y+1, 4, BLACK, WHITE);
      break;
    case MODE_EXP:
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y+1, 0, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y+1, 1, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y+1, 2, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y+1, 3, BLACK, WHITE);
      uMultimeterUI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y+1, 4, WHITE, BLACK);
      break;
    default:
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
