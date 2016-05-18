/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"

#include "uMultimeter.h"
#include "uMultimeter_ui.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define UI_PutChar      OLED_PutChar
#define UI_PutChar16    OLED_PutChar16
#define UI_PutChar32    OLED_PutChar32
#define UI_DrawRect     OLED_DrawRect
#define UI_DrawRectFill OLED_DrawRectFill
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
#define SEL_WINDOW_X (0)
#define SEL_WINDOW_Y (OLED_H - 1 - 8)

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

void UM_UI_menuDisplay_button( uint8_t posX, uint8_t posY, uint8_t select, uint16_t fontColor, uint16_t backColor )
{
  UI_PutChar16(posX + 1, posY + 1, 5, 16, fontMatrix_5x16[select], fontColor, backColor);
  UI_DrawRect(posX, posY, 18, 7, backColor);
}
void UM_UI_menuDisplay( uint32_t mode )
{
  uint8_t tmpMode  = Byte32U8_2(mode);
  uint8_t tmpModeS = Byte32U8_1(mode);
  
  switch(tmpMode) {
    case MODE_VOL:
      if(tmpModeS == MODE_VOL_CH1)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 7, WHITE, BLACK);
      else if(tmpModeS == MODE_VOL_CH2)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 8, WHITE, BLACK);
      else
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 9, WHITE, BLACK);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 1, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 2, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 3, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y + 1, 4, BLACK, WHITE);
      break;
    case MODE_RES:
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 0, BLACK, WHITE);
      if(tmpModeS == MODE_RES_RES)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 1, WHITE, BLACK);
      else
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 10, WHITE, BLACK);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 2, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 3, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y + 1, 4, BLACK, WHITE);
      break;
    case MODE_PWM:
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 0, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 1, BLACK, WHITE);
      if(tmpModeS == MODE_PWM_OUT)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 5, WHITE, BLACK);
      else
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 6, WHITE, BLACK);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 3, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y + 1, 4, BLACK, WHITE);
      break;
    case MODE_WAV:
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 0, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 1, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 2, BLACK, WHITE);
      if(tmpModeS == MODE_WAV_CH1)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 7, WHITE, BLACK);
      else if(tmpModeS == MODE_WAV_CH2)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 8, WHITE, BLACK);
      else if(tmpModeS == MODE_WAV_ALL)
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 11, WHITE, BLACK);
      else
        UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 4, WHITE, BLACK);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y + 1, 4, BLACK, WHITE);
      break;
    case MODE_EXP:
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*0, SEL_WINDOW_Y + 1, 0, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*1, SEL_WINDOW_Y + 1, 1, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*2, SEL_WINDOW_Y + 1, 2, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*3, SEL_WINDOW_Y + 1, 3, BLACK, WHITE);
      UM_UI_menuDisplay_button(SEL_WINDOW_X + 1 + 19*4, SEL_WINDOW_Y + 1, 4, WHITE, BLACK);
      break;
    default:
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint16_t UI_charArray_V5x16_CH1[5] = {0x3A58,0x4249,0x43C8,0x4249,0x3A5C}; // CH1:
const uint16_t UI_charArray_V5x16_CH2[5] = {0x3A5C,0x4245,0x43DC,0x4251,0x3A5C}; // CH2:
const uint16_t UI_charArray_V5x9_DC[5]   = {0x01C7,0x0128,0x0128,0x0128,0x01C7}; // DC
const uint16_t UI_charArray_V5x9_AC[5]   = {0x00C7,0x0128,0x0128,0x01E8,0x0127}; // AC
const uint16_t UI_charArray_V16x16_m[22] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xCE3C,0xFF7E,0xE3C7,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183,0xC183};  // 16x16 m
const uint16_t UI_charArray_V16x16_V[22] = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xE01C,0xE01C,0x6038,0x7038,0x7030,0x3070,0x3870,0x3860,0x18E0,0x18E0,0x1CC0,0x0DC0,0x0D80,0x0D80,0x0780,0x0700};  // 16x16 V

void UM_UI_modeVOL_putNum5x3( uint8_t posX, uint8_t posY, uint16_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[4] = {0};

  getNumDigit(num, number);

  for(int8_t i = 0; i < 4; i++)
    UI_PutChar(posX + i*4, posY, 5, 4, ASCII_NUM_5x3[num[3 - i]], fontColor, backColor);
}
void UM_UI_modeVOL_putBigNum16x16( uint8_t posX, uint8_t posY, uint16_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[5] = {0};

  if(number < 1000) {
    getNumDigit(num, number);
    if(num[2] == 0)
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], backColor, backColor);
    else
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], fontColor, backColor);
    if((num[2] == 0) && (num[1] == 0))
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[1]], backColor, backColor);
    else
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[1]], fontColor, backColor);
    UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[0]], fontColor, backColor);
    UI_PutChar16(posX + 51, posY, 22, 16, UI_charArray_V16x16_m, fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_V16x16_V, fontColor, backColor);
  }
  else if((number >= 1000) && (number < 10000)) {
    if(number%10 < 5)
      getNumDigit(num, number);
    else
      getNumDigit(num, number + 5);
    UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[3]], fontColor, backColor);
    UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[10], fontColor, backColor);
    UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], fontColor, backColor);
    UI_PutChar16(posX + 3*17, posY, 22, 16, ASCII_NUM_22x16[num[1]], fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_V16x16_V, fontColor, backColor);
  }
  else {
    if(number%100 < 50)
      getNumDigit(num, number);
    else
      getNumDigit(num, number + 50);
    UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[4]], fontColor, backColor);
    UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[3]], fontColor, backColor);
    UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[10], fontColor, backColor);
    UI_PutChar16(posX + 3*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_V16x16_V, fontColor, backColor);
  }
}

#define MODE_VOL_CH1_X    (0)
#define MODE_VOL_CH1_Y    (0)
#define MODE_VOL_NUM1_X   (MODE_VOL_CH1_X + 18)
#define MODE_VOL_NUM1_Y   (MODE_VOL_CH1_Y)
#define MODE_VOL_CH2_X    (MODE_VOL_CH1_X + 40)
#define MODE_VOL_CH2_Y    (MODE_VOL_CH1_Y)
#define MODE_VOL_NUM2_X   (MODE_VOL_CH2_X + 18)
#define MODE_VOL_NUM2_Y   (MODE_VOL_CH2_Y)
#define MODE_VOL_DCAC_X   (82)
#define MODE_VOL_DCAC_Y   (MODE_VOL_CH1_Y)
#define MODE_VOL_BIGN_X   (7)
#define MODE_VOL_BIGN_Y   (22)
void UM_UI_modeVOL_setMode( uint8_t mode )
{
  if(!mode) UI_PutChar16(MODE_VOL_DCAC_X, MODE_VOL_DCAC_Y, 5, 9, UI_charArray_V5x9_DC, WHITE, BLACK);
  else      UI_PutChar16(MODE_VOL_DCAC_X, MODE_VOL_DCAC_Y, 5, 9, UI_charArray_V5x9_AC, WHITE, BLACK);
}
void UM_UI_modeVOL_Init( uint8_t mode )
{
  UI_DrawRectFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  UI_PutChar16(MODE_VOL_CH1_X, MODE_VOL_CH1_Y, 5, 16, UI_charArray_V5x16_CH1, GREEN, BLACK);
  UI_PutChar16(MODE_VOL_CH2_X, MODE_VOL_CH2_Y, 5, 16, UI_charArray_V5x16_CH2,  BLUE, BLACK);
  UM_UI_modeVOL_setMode(0);
  UM_UI_modeVOL(0, 0, 0);
}
void UM_UI_modeVOL( uint16_t number_ch1, uint16_t number_ch2, uint16_t number )
{
  static uint16_t tmpData = 0;
  uint16_t deltaData = 0;

  UM_UI_modeVOL_putNum5x3(MODE_VOL_NUM1_X, MODE_VOL_NUM1_Y, number_ch1, WHITE, BLACK);
  UM_UI_modeVOL_putNum5x3(MODE_VOL_NUM2_X, MODE_VOL_NUM2_Y, number_ch2, WHITE, BLACK);

  deltaData = (number > tmpData) ? number - tmpData : tmpData - number;
  if(deltaData > 40) {  // delat > 40 mV
    UI_DrawRectFill(MODE_VOL_DCAC_X + 12, MODE_VOL_DCAC_Y, 2, 5, RED);
    tmpData = number;
  }
  else
    UI_DrawRectFill(MODE_VOL_DCAC_X + 12, MODE_VOL_DCAC_Y, 2, 5, BLACK);

  UM_UI_modeVOL_putBigNum16x16(MODE_VOL_BIGN_X, MODE_VOL_BIGN_Y, number, WHITE, BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint16_t UI_charArray_R5x16_BEEP[5] = {0xE777,0x9445,0xE667,0x9444,0xE774}; // BEEP
const uint16_t UI_charArray_R5x16_DIO[5]  = {0x0460,0x05E0,0x7FFE,0x05E0,0x0460}; // DIODE
const uint16_t UI_charArray_R5x16_RES[5]  = {0x0FF0,0x0FF0,0x7FFE,0x0FF0,0x0FF0}; // RES
const uint32_t UI_charArray_R5x21_CODE[5] = {0x000E6738,0x001094A2,0x001094B0,0x001094A2,0x000E6738}; // CODE:
const uint16_t UI_charArray_R16x16_K[22]  = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xC070,0xC0E0,0xC1C0,0xC380,0xC700,0xCE00,0xDC00,0xF800,0xFC00,0xCE00,0xC700,0xC380,0xC1C0,0xC0E0,0xC070,0xC078};  // 16x16 m
const uint16_t UI_charArray_R16x16_R[22]  = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFF80,0xFFC0,0xC1E0,0xC0E0,0xC0E0,0xC0E0,0xC1C0,0xFF80,0xFF00,0xC780,0xC380,0xC1C0,0xC0E0,0xC060,0xC070,0xC038};  // 16x16 V

void UM_UI_modeRES_putCodeNum5x3( uint8_t posX, uint8_t posY, uint32_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[7] = {0};
  uint8_t length = 0;

  length = getNumDigit(num, number);

  if(number == 0) {
    UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
  }
  else if(length == 1) {
    UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
    UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[0]], WHITE, BLACK);
    UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[0], WHITE, BLACK);
  }
  else {
    UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[length - 1]], WHITE, BLACK);
    UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[length - 2]], WHITE, BLACK);
    UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[length - 2], WHITE, BLACK);
  }
}

void UM_UI_modeRES_putBigNum16x16( uint8_t posX, uint8_t posY, uint32_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[7] = {0};

  getNumDigit(num, number);

  if(number < 1000) {
    UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[0], backColor, backColor);
    if(num[2] == 0)
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], backColor, backColor);
    else
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], fontColor, backColor);
    if((num[2] == 0) && (num[1] == 0))
      UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[1]], backColor, backColor);
    else
      UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[1]], fontColor, backColor);
    UI_PutChar16(posX + 3*17, posY, 22, 16, ASCII_NUM_22x16[num[0]], fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_R16x16_R, fontColor, backColor);
  }
  else if((number >= 1000) && (number < 100000)) {
    if(num[4] == 0)
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[4]], backColor, backColor);
    else
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[4]], fontColor, backColor);
    UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[3]], fontColor, backColor);
    UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[10],     fontColor, backColor);
    UI_PutChar16(posX + 3*17, posY, 22, 16, ASCII_NUM_22x16[num[2]], fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_R16x16_K, fontColor, backColor);
  }
  else {
    if(num[6] == 0)
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[6]], backColor, backColor);
    else
      UI_PutChar16(posX + 0*17, posY, 22, 16, ASCII_NUM_22x16[num[6]], fontColor, backColor);
    if((num[6] == 0) && (num[5] == 0))
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[5]], backColor, backColor);
    else
      UI_PutChar16(posX + 1*17, posY, 22, 16, ASCII_NUM_22x16[num[5]], fontColor, backColor);
    if((num[6] == 0) && (num[5] == 0) && (num[4] == 0))
      UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[4]], backColor, backColor);
    else
      UI_PutChar16(posX + 2*17, posY, 22, 16, ASCII_NUM_22x16[num[4]], fontColor, backColor);
    UI_PutChar16(posX + 3*17, posY, 22, 16, ASCII_NUM_22x16[num[3]], fontColor, backColor);
    UI_PutChar16(posX + 72, posY, 22, 16, UI_charArray_R16x16_K, fontColor, backColor);
  }
}

#define MODE_RES_BEEP_X   (0)
#define MODE_RES_BEEP_Y   (0)
#define MODE_RES_MODE_X   (20)
#define MODE_RES_MODE_Y   (MODE_RES_BEEP_Y)
#define MODE_RES_CODE_X   (61)
#define MODE_RES_CODE_Y   (MODE_RES_BEEP_Y)
#define MODE_RES_BIGN_X   (7)
#define MODE_RES_BIGN_Y   (22)
void UM_UI_modeRES_setBeep( uint8_t mode )
{
  uint16_t tmpMode = (mode) ? YELLOW : WHITE;

  UI_PutChar16(MODE_RES_BEEP_X, MODE_RES_BEEP_Y, 5, 16, UI_charArray_R5x16_BEEP, tmpMode, BLACK);
}
void UM_UI_modeRES_setMode( uint8_t mode )
{
  if(mode == MODE_RES_DIO) {
    UI_PutChar16(MODE_RES_MODE_X + 0*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_DIO,  BLUE, BLACK);
    UI_PutChar16(MODE_RES_MODE_X + 1*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_RES, BLACK, BLACK);
  }
  else {
    UI_PutChar16(MODE_RES_MODE_X + 0*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_DIO, BLACK, BLACK);
    UI_PutChar16(MODE_RES_MODE_X + 1*19, MODE_RES_MODE_Y, 5, 16, UI_charArray_R5x16_RES, GREEN, BLACK);
  }
}
void UM_UI_modeRES_Init( uint8_t mode )
{
  UI_DrawRectFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  UI_PutChar32(MODE_RES_CODE_X, MODE_RES_CODE_Y, 5, 21, UI_charArray_R5x21_CODE, WHITE, BLACK);

  UM_UI_modeRES_setBeep(1);
  UM_UI_modeRES_setMode(mode);
}
void UM_UI_modeRES_RES( uint32_t number, uint8_t beepState )
{
  UM_UI_modeRES_setBeep(beepState);

  UM_UI_modeRES_putCodeNum5x3(MODE_RES_CODE_X + 21, MODE_RES_CODE_Y, number, WHITE, BLACK);
  UM_UI_modeRES_putBigNum16x16(MODE_RES_BIGN_X, MODE_RES_BIGN_Y, number, WHITE, BLACK);
}
void UM_UI_modeRES_DIO( uint32_t BigNum, uint8_t BeepState )
{
  UM_UI_modeRES_setBeep(BeepState);

  UM_UI_modeRES_putCodeNum5x3(MODE_RES_CODE_X + 21, MODE_RES_CODE_Y, 0, WHITE, BLACK);
  UM_UI_modeVOL_putBigNum16x16(MODE_RES_BIGN_X, MODE_RES_BIGN_Y, BigNum, WHITE, BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
const uint8_t  UI_charArray_P5x6_D[5]    = {0x38,0x25,0x24,0x25,0x38}; // D:
const uint8_t  UI_charArray_P5x6_F[5]    = {0x3C,0x21,0x38,0x21,0x20}; // F:
const uint8_t  UI_charArray_P5x6_P[5]    = {0x19,0x12,0x04,0x09,0x13}; // %
const uint16_t UI_charArray_P5x13_HZ[5]  = {0x0120,0x012F,0x01E2,0x0124,0x012F}; // HZ
const uint16_t UI_charArray_P5x13_KHZ[5] = {0x1120,0x112F,0x15E2,0x1924,0x152F}; // KHZ

void UM_UI_modePWM_putDutyNum5x4( uint8_t posX, uint8_t posY, uint16_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t  num[5] = {0};

  getNumDigit(num, number);

  if(num[4] == 0)
    UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[4]], backColor, backColor);
  else
    UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[4]], fontColor, backColor);
  if((num[4] == 0) && (num[3] == 0))
    UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[3]], backColor, backColor);
  else
    UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[3]], fontColor, backColor);
  UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[num[2]], fontColor, backColor);
  UI_PutChar(posX + 3*4, posY, 5, 4, ASCII_NUM_5x3[10],     fontColor, backColor);
  UI_PutChar(posX + 4*4, posY, 5, 4, ASCII_NUM_5x3[num[1]], fontColor, backColor);
  UI_PutChar(posX + 5*4, posY, 5, 4, ASCII_NUM_5x3[num[0]], fontColor, backColor);
}
void UM_UI_modePWM_putFreqNum5x4( uint8_t posX, uint8_t posY, uint32_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[7] = {0};

  getNumDigit(num, number);

  if(number < 10000) {
    if(num[3] == 0)
      UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[3]], backColor, backColor);
    else
      UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[3]], fontColor, backColor);
    if((num[3] == 0) && (num[2] == 0))
      UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[2]], backColor, backColor);
    else
      UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[2]], fontColor, backColor);
    if((num[3] == 0) && (num[2] == 0) && (num[1] == 0))
      UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[num[1]], backColor, backColor);
    else
      UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[num[1]], fontColor, backColor);
    UI_PutChar(posX + 3*4, posY, 5, 4, ASCII_NUM_5x3[num[0]], fontColor, backColor);

    UI_PutChar16(posX + 18, posY, 5, 13, UI_charArray_P5x13_HZ, fontColor, backColor);
  }
  else {
    if(num[6] == 0)
      UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[6]], backColor, backColor);
    else
      UI_PutChar(posX + 0*4, posY, 5, 4, ASCII_NUM_5x3[num[6]], fontColor, backColor);
    if((num[6] == 0) && (num[5] == 0))
      UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[5]], backColor, backColor);
    else
      UI_PutChar(posX + 1*4, posY, 5, 4, ASCII_NUM_5x3[num[5]], fontColor, backColor);
    if((num[6] == 0) && (num[5] == 0) && (num[4] == 0))
      UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[num[4]], backColor, backColor);
    else
      UI_PutChar(posX + 2*4, posY, 5, 4, ASCII_NUM_5x3[num[4]], fontColor, backColor);
    UI_PutChar(posX + 3*4, posY, 5, 4, ASCII_NUM_5x3[num[3]], fontColor, backColor);

    UI_PutChar16(posX + 18, posY, 5, 13, UI_charArray_P5x13_KHZ, fontColor, backColor);
  }
}

#define WAVE_H    (32)
#define WAVE_W    (60)
#define WAVE_X_W  (8)
#define WAVE_X_H  (3)
void UM_UI_modePWM_putPLUSE( uint8_t posX, uint8_t posY, uint16_t duty, uint16_t LineColor, uint16_t backColor )
{
  static uint8_t oldDuty = 0;
  uint8_t newDuty = duty * 0.006f;  // 0 ~ 100.00% -> 0 ~ 60

  if(newDuty == oldDuty) {
  
  }
  else if(newDuty > oldDuty) {
    UI_DrawRect(posX + WAVE_X_W + oldDuty - 2, posY, newDuty - oldDuty + 1, WAVE_H, backColor);
    UI_DrawRectFill(posX + WAVE_X_W + oldDuty - 1, posY, newDuty - oldDuty - 1, WAVE_X_H, backColor);
  }
  else {
    UI_DrawRect(posX + WAVE_X_W + newDuty - 2, posY, oldDuty - newDuty + 1, WAVE_H, backColor);
    UI_DrawRectFill(posX + WAVE_X_W + newDuty - 1, posY + WAVE_H - WAVE_X_H, oldDuty - newDuty - 1, WAVE_X_H, backColor);
  }

  UI_DrawRectFill(posX,                          posY + WAVE_H - WAVE_X_H, WAVE_X_W,             WAVE_X_H, LineColor);
  UI_DrawRectFill(posX + WAVE_X_W - 1,           posY,                     newDuty,              WAVE_X_H, LineColor);
  UI_DrawRectFill(posX + WAVE_X_W + newDuty - 2, posY + WAVE_H - WAVE_X_H, WAVE_W - newDuty + 1, WAVE_X_H, LineColor);
  UI_DrawRectFill(posX + WAVE_X_W + WAVE_W - 2,  posY,                     WAVE_X_W,             WAVE_X_H, LineColor);

  OLED_DrawLineY(posX + WAVE_X_W - 1,           posY, WAVE_H, LineColor);
  OLED_DrawLineY(posX + WAVE_X_W + newDuty - 2, posY, WAVE_H, LineColor);
  OLED_DrawLineY(posX + WAVE_X_W + WAVE_W - 2,  posY, WAVE_H, LineColor);

  oldDuty = newDuty;
}

#define MODE_PWM_DUTY_X   (1)
#define MODE_PWM_DUTY_Y   (0)
#define MODE_PWM_NUM1_X   (MODE_PWM_DUTY_X + 6)
#define MODE_PWM_NUM1_Y   (MODE_PWM_DUTY_Y)
#define MODE_PWM_FREQ_X   (MODE_PWM_DUTY_X + 56)
#define MODE_PWM_FREQ_Y   (0)
#define MODE_PWM_NUM2_X   (MODE_PWM_FREQ_X + 6)
#define MODE_PWM_NUM2_Y   (MODE_PWM_FREQ_Y)
#define MODE_PWM_PLUSE_X  (12)
#define MODE_PWM_PLUSE_Y  (15)
void UM_UI_modePWM_Init( uint8_t mode )
{
  UI_DrawRectFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  UI_PutChar(MODE_PWM_DUTY_X, MODE_PWM_DUTY_Y, 5, 6, UI_charArray_P5x6_D, WHITE, BLACK);
  UI_PutChar(MODE_PWM_DUTY_X + 31, MODE_PWM_DUTY_Y, 5, 6, UI_charArray_P5x6_P, WHITE, BLACK);
  UI_PutChar(MODE_PWM_FREQ_X, MODE_PWM_FREQ_Y, 5, 6, UI_charArray_P5x6_F, WHITE, BLACK);
  UM_UI_modePWM_putDutyNum5x4(MODE_PWM_NUM1_X, MODE_PWM_NUM1_Y, 0, WHITE, BLACK);
  UM_UI_modePWM_putFreqNum5x4(MODE_PWM_NUM2_X, MODE_PWM_NUM2_Y, 0, WHITE, BLACK);
}
void UM_UI_modePWM( uint16_t duty, uint32_t freq )
{
  UM_UI_modePWM_putDutyNum5x4(MODE_PWM_NUM1_X, MODE_PWM_NUM1_Y, duty, WHITE, BLACK);
  UM_UI_modePWM_putFreqNum5x4(MODE_PWM_NUM2_X, MODE_PWM_NUM2_Y, freq, WHITE, BLACK);
  UM_UI_modePWM_putPLUSE(MODE_PWM_PLUSE_X, MODE_PWM_PLUSE_Y, duty, GREEN, BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*/
void UM_UI_modeWAV_putNum5x3( uint8_t posX, uint8_t posY, int16_t number, uint16_t fontColor, uint16_t backColor )
{
  uint8_t num[4] = {0};

  if(number < 0) {
    number = -number;
    UI_PutChar(posX, posY, 5, 4, ASCII_NUM_5x3[12], fontColor, backColor);
  }
  else {
    UI_PutChar(posX, posY, 5, 4, ASCII_NUM_5x3[11], fontColor, backColor);
  }
  getNumDigit(num, number);

  for(int8_t i = 0; i < 4; i++)
    UI_PutChar(posX + i*4 + 4, posY, 5, 4, ASCII_NUM_5x3[num[3 - i]], fontColor, backColor);
}

#define MODE_WAV_CH1_X   (2)
#define MODE_WAV_CH1_Y   (1)
#define MODE_WAV_CH2_X   (50)
#define MODE_WAV_CH2_Y   (MODE_WAV_CH1_Y)

void UM_UI_modeWAV_Init( uint8_t mode )
{
  UI_DrawRectFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  UI_DrawRectFill(0, 0, 96, 6, WHITE);
  UI_DrawRectFill(MODE_WAV_CH1_X, MODE_WAV_CH1_Y, 16, 5, GREEN);
  UI_DrawRectFill(MODE_WAV_CH2_X, MODE_WAV_CH1_Y, 16, 5, BLUE);
}
void UM_UI_modeWAV_CH1( WaveForm_Struct *pWaveForm )
{
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH1_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[0], BLACK, WHITE);
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH2_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[1], BLACK, WHITE);

  pWaveForm->PointColor[0] = BLACK;
  pWaveForm->PointColor[1] = GREEN;
  pWaveForm->Data[1] = pWaveForm->Data[0];
  WaveFormPrint(pWaveForm, ENABLE);
}
void UM_UI_modeWAV_CH2( WaveForm_Struct *pWaveForm )
{
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH1_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[0], BLACK, WHITE);
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH2_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[1], BLACK, WHITE);

  pWaveForm->PointColor[0] = BLACK;
  pWaveForm->PointColor[1] = BLUE;
  pWaveForm->Data[0] = pWaveForm->Data[1];
  WaveFormPrint(pWaveForm, ENABLE);
}
void UM_UI_modeWAV_ALL( WaveForm_Struct *pWaveForm )
{
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH1_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[0], BLACK, WHITE);
  UM_UI_modeWAV_putNum5x3(MODE_WAV_CH2_X + 18, MODE_WAV_CH1_Y, pWaveForm->Data[1], BLACK, WHITE);

  pWaveForm->PointColor[0] = GREEN;
  pWaveForm->PointColor[1] = BLUE;
  WaveFormPrint(pWaveForm, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*/
#define MODE_EXP_X  (4)
#define MODE_EXP_Y  (1)

void UM_UI_modeEXP_Init( uint8_t mode )
{
  UI_DrawRectFill(0, 0, OLED_W, OLED_H - 9, BLACK);
  UI_DrawRectFill(0, 0, 11, 11, GREEN);
  UI_DrawRectFill(14, 0, 5, 11, BLUE);
  UI_DrawRectFill(22, 0, 74, 11, WHITE);

  switch(mode) {
    case MODE_EXP_NUL:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, "ExpNUL",  BLACK, WHITE);  break;
//    case MODE_EXP_POW:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpPOW",  BLACK, WHITE);  break;
//    case MODE_EXP_POT:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpPOT",  BLACK, WHITE);  break;
//    case MODE_EXP_CUR:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpCUR",  BLACK, WHITE);  break;
//    case MODE_EXP_ADC:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpADC",  BLACK, WHITE);  break;
//    case MODE_EXP_DAC:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpDAC",  BLACK, WHITE);  break;
//    case MODE_EXP_MOI:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpMOI",  BLACK, WHITE);  break;
//    case MODE_EXP_ROT:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpROT",  BLACK, WHITE);  break;
//    case MODE_EXP_MAG:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpMAG",  BLACK, WHITE);  break;
//    case MODE_EXP_IMU:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpIMU",  BLACK, WHITE);  break;
//    case MODE_EXP_MIC:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpMIC",  BLACK, WHITE);  break;
//    case MODE_EXP_BMP:  OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpBMP",  BLACK, WHITE);  break;
//    case MODE_EXP_TEMP: OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpTEMP", BLACK, WHITE);  break;
//    case MODE_EXP_RFLW: OLED_PutStr_5x7(MODE_EXP_X + 24, MODE_EXP_Y, (int8_t*)"ExpRFLW", BLACK, WHITE);  break;
    default:              break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
