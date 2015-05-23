/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_spi.h"
#include "module_ssd1331.h"
#include "algorithm_string.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define OLED_SPIx            SPI1
#define OLED_SPIx_CLK        RCC_APB2Periph_SPI1

#define OLED_DC_PIN          GPIO_Pin_1
#define OLED_DC_GPIO_PORT    GPIOA
#define OLED_DC_GPIO_CLK     RCC_APB2Periph_GPIOA
#define OLED_DC_H            GPIO_SetBits(OLED_DC_GPIO_PORT, OLED_DC_PIN)
#define OLED_DC_L            GPIO_ResetBits(OLED_DC_GPIO_PORT, OLED_DC_PIN)

#define OLED_RST_PIN         GPIO_Pin_2
#define OLED_RST_GPIO_PORT   GPIOA
#define OLED_RST_GPIO_CLK    RCC_APB2Periph_GPIOA
#define OLED_RST_H           GPIO_SetBits(OLED_RST_GPIO_PORT, OLED_RST_PIN)
#define OLED_RST_L           GPIO_ResetBits(OLED_RST_GPIO_PORT, OLED_RST_PIN)

#define OLED_CST_PIN         GPIO_Pin_4
#define OLED_CST_GPIO_PORT   GPIOA
#define OLED_CST_GPIO_CLK    RCC_APB2Periph_GPIOA
#define OLED_CST_H           GPIO_SetBits(OLED_CST_GPIO_PORT, OLED_CST_PIN)
#define OLED_CST_L           GPIO_ResetBits(OLED_CST_GPIO_PORT, OLED_CST_PIN)

#define OLED_SCK_PIN         GPIO_Pin_5
#define OLED_SCK_GPIO_PORT   GPIOA
#define OLED_SCK_GPIO_CLK    RCC_APB2Periph_GPIOA

#define OLED_SDI_PIN         GPIO_Pin_7
#define OLED_SDI_GPIO_PORT   GPIOA
#define OLED_SDI_GPIO_CLK    RCC_APB2Periph_GPIOA
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SSD1331_Config
**功能 : GPIO & SPI Config
**輸入 : None
**輸出 : None
**使用 : SSD1331_Config();
**====================================================================================================*/
/*====================================================================================================*/
void SSD1331_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  /* SPI Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(OLED_RST_GPIO_CLK | OLED_CST_GPIO_CLK | OLED_DC_GPIO_CLK  | 
                         OLED_SCK_GPIO_CLK | OLED_SDI_GPIO_CLK | OLED_SPIx_CLK     |
                         RCC_APB2Periph_AFIO, ENABLE);

  /* DC PB10  */
  GPIO_InitStruct.GPIO_Pin = OLED_DC_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(OLED_DC_GPIO_PORT, &GPIO_InitStruct);
  /* RST PB11 */
  GPIO_InitStruct.GPIO_Pin = OLED_RST_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(OLED_RST_GPIO_PORT, &GPIO_InitStruct);
  /* CST PB12  */
  GPIO_InitStruct.GPIO_Pin = OLED_CST_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(OLED_CST_GPIO_PORT, &GPIO_InitStruct);
  /* SCK PB13 */
  GPIO_InitStruct.GPIO_Pin = OLED_SCK_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(OLED_SCK_GPIO_PORT, &GPIO_InitStruct);
  /* SDI PB15 */
  GPIO_InitStruct.GPIO_Pin = OLED_SDI_PIN;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(OLED_SDI_GPIO_PORT, &GPIO_InitStruct);

  OLED_CST_H;  // 低電位有效

  /* SPI Init ****************************************************************/
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   // Full Duplex
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;                        // Master Mode
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;                    // Data Size 8 bit
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;                          // Transitioned On The Falling Edge
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;                         // Latched On the Rising Edge
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;                            // Software NSS Signal
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;   // fsck = APB1 36MHz / 2 = 18MHz
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;                   // MSB First
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(OLED_SPIx, &SPI_InitStruct);

  SPI_Cmd(OLED_SPIx, ENABLE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_WriteCmd
**功能 : Write Command or Address
**輸入 : WriteCmd
**輸出 : None
**使用 : OLED_WriteCmd(0xCB);
**====================================================================================================*/
/*====================================================================================================*/
static void OLED_WriteCmd( uint8_t WriteCmd )
{
  OLED_CST_L;
  OLED_DC_L;
  SPI_RW(OLED_SPIx, WriteCmd);
  OLED_CST_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_WriteData
**功能 : Write Data
**輸入 : WriteData
**輸出 : None
**使用 : OLED_WriteData(Byte8H(Color));
**====================================================================================================*/
/*====================================================================================================*/
//static void OLED_WriteData( uint8_t WriteData )
//{
//  OLED_CST_L;
//  OLED_DC_H;
//  SPI_RW(OLED_SPIx, WriteData);
//  OLED_CST_H;
//}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_WriteColor
**功能 : Write Color
**輸入 : Color
**輸出 : None
**使用 : OLED_WriteColor(BLACK);
**====================================================================================================*/
/*====================================================================================================*/
static void OLED_WriteColor( uint16_t Color )
{
  OLED_CST_L;
  OLED_DC_H;
  SPI_RW(OLED_SPIx, Byte8H(Color));
  SPI_RW(OLED_SPIx, Byte8L(Color));
  OLED_CST_H;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : SSD1331_Init
**功能 : SSD1331 Init
**輸入 : None
**輸出 : None
**使用 : SSD1331_Init();
**====================================================================================================*/
/*====================================================================================================*/
void SSD1331_Init( void )
{
  // Hardware Reset
  OLED_RST_L;
  Delay_1ms(15);
  OLED_RST_H;
  Delay_1ms(50);

  // Device Init
  OLED_Display(DISABLE); // Display Off

  OLED_WriteCmd(0x81);   // Set Contrast for Color A
  OLED_WriteCmd(0x91);   // 145
  OLED_WriteCmd(0x82);   // Set Contrast for Color B
  OLED_WriteCmd(0x50);   // 80
  OLED_WriteCmd(0x83);   // Set Contrast for Color C
  OLED_WriteCmd(0x7D);   // 125

	OLED_WriteCmd(0x87);   // Master Contrast Current Control
	OLED_WriteCmd(0x06);   // 6

  OLED_WriteCmd(0x8A);   // Set Second Pre-change Speed for Color A
  OLED_WriteCmd(0x64);   // 100
  OLED_WriteCmd(0x8B);   // Set Second Pre-change Speed for Color B
  OLED_WriteCmd(0x78);   // 120
  OLED_WriteCmd(0x8C);   // Set Second Pre-change Speed for Color C
  OLED_WriteCmd(0x64);   // 100

	OLED_WriteCmd(0xA0);   // Set Remap & Color Depth
	OLED_WriteCmd(0x72);   // 0x72

	OLED_WriteCmd(0xA1);   // Set Display Start Line
	OLED_WriteCmd(0x00);   // 0

	OLED_WriteCmd(0xA2);   // Set Display Offset
	OLED_WriteCmd(0x00);   // 0

	OLED_WriteCmd(0xA4);   // Set Display Mode

	OLED_WriteCmd(0xA8);   // Set Multiplex Ratio
	OLED_WriteCmd(0x3F);   // 0x3F

	OLED_WriteCmd(0xAD);   // Set  Master Configuration
	OLED_WriteCmd(0x8E);   // 0x8E

  OLED_WriteCmd(0xB0);   // Set Power Save Mode
	OLED_WriteCmd(0x00);   // 0x00

	OLED_WriteCmd(0xB1);   // Phase 1 and 2 Period Adjustment
	OLED_WriteCmd(0x31);   // 0x31

	OLED_WriteCmd(0xB3);   // Set Display Clock Divider / Oscillator Frequency
	OLED_WriteCmd(0xF0);   // 0xF0

	OLED_WriteCmd(0xBB);   // Set Pre-change Level
	OLED_WriteCmd(0x3A);   // 0x3A

	OLED_WriteCmd(0xBE);   // Set vcomH
	OLED_WriteCmd(0x3E);   // 0x3E

	OLED_WriteCmd(0x2E);   // Disable Scrolling

  OLED_Display(ENABLE);
  OLED_Clear(WHITE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_Display
**功能 : OLED Display
**輸入 : Cmd
**輸出 : None
**使用 : OLED_Display(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_Display( uint8_t Cmd )
{
  if(Cmd == ENABLE)
    OLED_WriteCmd(0xAF);
  else
    OLED_WriteCmd(0xAE);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_Clear
**功能 : Clear Window
**輸入 : Color
**輸出 : None
**使用 : OLED_Clear(BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_Clear( uint16_t Color )
{
  uint32_t point = OLED_W * OLED_H;

  OLED_SetWindow(0, 0, OLED_W-1, OLED_H-1);

  while(point--)
    OLED_WriteColor(Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_SetWindow
**功能 : Set Window
**輸入 : StartX, StartY, EndX, EndY
**輸出 : None
**使用 : OLED_SetWindow(X0, Y0, X1, Y1);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_SetWindow( uint8_t StartX, uint8_t StartY, uint8_t EndX, uint8_t EndY )
{
  OLED_WriteCmd(0x15);
  OLED_WriteCmd(StartX);
  OLED_WriteCmd(EndX);
  OLED_WriteCmd(0x75);
  OLED_WriteCmd(StartY);
  OLED_WriteCmd(EndY);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawPixel
**功能 : Draw a Pixel
**輸入 : CoordiX, CoordiY, Color
**輸出 : None
**使用 : OLED_DrawPixel(CoordiX, CoordiY, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawPixel( uint8_t CoordiX, uint8_t CoordiY, uint16_t Color )
{
  OLED_SetWindow(CoordiX, CoordiY, OLED_W - 1, OLED_H - 1);
  OLED_WriteColor(Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawLine
**功能 : Draw Line
**輸入 : StartX, StartY, EndX, EndY, Color
**輸出 : None
**使用 : OLED_DrawLine(StartX, StartY, EndX, EndY, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawLine( uint8_t StartX, uint8_t StartY, uint8_t EndX, uint8_t EndY, uint16_t Color )
{
  OLED_WriteCmd(0x21);
  OLED_WriteCmd(StartX);
  OLED_WriteCmd(StartY);
  OLED_WriteCmd(EndX);
  OLED_WriteCmd(EndY);
  OLED_WriteCmd(RGB565_R(Color));
  OLED_WriteCmd(RGB565_G(Color));
  OLED_WriteCmd(RGB565_B(Color));
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawLineX
**功能 : Draw X-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : OLED_DrawLineX(CoordiX, CoordiY, Length, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawLineX( uint8_t CoordiX, uint8_t CoordiY, uint8_t Length, uint16_t Color )
{
  OLED_SetWindow(CoordiX, CoordiY, CoordiX+Length-1, CoordiY);

  while(Length--)
    OLED_WriteColor(Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawLineY
**功能 : Draw Y-Axis Line
**輸入 : CoordiX, CoordiY, Length, Color
**輸出 : None
**使用 : OLED_DrawLineY(CoordiX, CoordiY, Length, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawLineY( uint8_t CoordiX, uint8_t CoordiY, uint8_t Length, uint16_t Color )
{
  OLED_SetWindow(CoordiX, CoordiY, CoordiX, CoordiY+Length-1);

  while(Length--)
    OLED_WriteColor(Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawRectangle
**功能 : Draw Rectangle
**輸入 : CoordiX, CoordiY, Length, Width, Color
**輸出 : None
**使用 : OLED_DrawRectangle(CoordiX, CoordiY, Width, Height, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawRectangle( uint8_t CoordiX, uint8_t CoordiY, uint8_t Width, uint8_t Height, uint16_t Color )
{
  OLED_DrawLineX(CoordiX,         CoordiY,          Width,   Color);
  OLED_DrawLineX(CoordiX,         CoordiY+Height-1, Width,   Color);
  OLED_DrawLineY(CoordiX,         CoordiY,          Height,  Color);
  OLED_DrawLineY(CoordiX+Width-1, CoordiY,          Height,  Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawRectangleFill
**功能 : Draw Rectangle
**輸入 : CoordiX, CoordiY, Length, Width, Color
**輸出 : None
**使用 : OLED_DrawRectangleFill(CoordiX, CoordiY, Width, Height, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawRectangleFill( uint8_t CoordiX, uint8_t CoordiY, uint8_t Width, uint8_t Height, uint16_t Color )
{
  uint32_t Point = Width * Height;

  OLED_SetWindow(CoordiX, CoordiY, CoordiX+Width-1, CoordiY+Height-1);

  while(Point--)
    OLED_WriteColor(Color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_DrawCircle
**功能 : Draw Circle
**輸入 : CoordiX, CoordiY, Radius, Color
**輸出 : None
**使用 : OLED_DrawCircle(CoordiX, CoordiY, Radius, Color);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_DrawCircle( uint8_t CoordiX, uint8_t CoordiY, uint8_t Radius, uint16_t Color )
{
	int16_t x = -Radius;
  int16_t y = 0;
  int16_t err = 2 - 2 * Radius;
  int16_t e2;

  do {
    OLED_DrawPixel(CoordiX - x, CoordiY + y, Color);
    OLED_DrawPixel(CoordiX + x, CoordiY + y, Color);
    OLED_DrawPixel(CoordiX + x, CoordiY - y, Color);
    OLED_DrawPixel(CoordiX - x, CoordiY - y, Color);
    e2 = err;
    if(e2 <= y) {
      err += ++ y * 2 + 1;
      if(-x == y && e2 <= x)
        e2 = 0;
    }
    if(e2 > x)
      err += ++ x * 2 + 1;
  } while(x <= 0);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_PutChar
**功能 : Put Char
**輸入 : CoordiX, CoordiY, CharH, CharW, pMatrix, FontColor, BackColor
**輸出 : None
**使用 : OLED_PutChar(x, y, 5, 3, ASCII_5x3['C'], WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_PutChar( uint8_t CoordiX, uint8_t CoordiY, uint8_t CharH, uint8_t CharW, const uint8_t *pMatrix, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t tmp = 0;

  for(uint8_t i = 0; i < CharH; i++) {
    tmp = pMatrix[i];
    for(uint8_t j = 0; j < CharW; j++) {
      if(((tmp >> (CharW-1-j)) & 0x01) == 0x01)
        OLED_DrawPixel(CoordiX+j, CoordiY+i, FontColor); // 字符顏色
      else
        OLED_DrawPixel(CoordiX+j, CoordiY+i, BackColor); // 背景顏色
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_PutChar16
**功能 : Put Char
**輸入 : CoordiX, CoordiY, CharH, CharW, pMatrix, FontColor, BackColor
**輸出 : None
**使用 : OLED_PutChar16(x, y, 12, 6, ASCII_12x6['C'], WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_PutChar16( uint8_t CoordiX, uint8_t CoordiY, uint8_t CharH, uint8_t CharW, const uint16_t *pMatrix, uint16_t FontColor, uint16_t BackColor )
{
  uint16_t tmp = 0;

  for(uint8_t i = 0; i < CharH; i++) {
    tmp = pMatrix[i];
    for(uint8_t j = 0; j < CharW; j++) {
      if(((tmp >> (CharW-1-j)) & 0x0001) == 0x0001)
        OLED_DrawPixel(CoordiX+j, CoordiY+i, FontColor); // 字符顏色
      else
        OLED_DrawPixel(CoordiX+j, CoordiY+i, BackColor); // 背景顏色
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_PutChar32
**功能 : Put Char
**輸入 : CoordiX, CoordiY, CharH, CharW, pMatrix, FontColor, BackColor
**輸出 : None
**使用 : OLED_PutChar32(x, y, 32, 24, ASCII_32x24['C'], WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_PutChar32( uint8_t CoordiX, uint8_t CoordiY, uint8_t CharH, uint8_t CharW, const uint32_t *pMatrix, uint16_t FontColor, uint16_t BackColor )
{
  uint32_t tmp = 0;

  for(uint8_t i = 0; i < CharH; i++) {
    tmp = pMatrix[i];
    for(uint8_t j = 0; j < CharW; j++) {
      if(((tmp >> (CharW-1-j)) & 0x0001) == 0x0001)
        OLED_DrawPixel(CoordiX+j, CoordiY+i, FontColor); // 字符顏色
      else
        OLED_DrawPixel(CoordiX+j, CoordiY+i, BackColor); // 背景顏色
    }
  }
}

void OLED_PutCharNum_7x6( uint8_t CoordiX, uint8_t CoordiY, int8_t ChWord, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t Tmp_Char = 0;
  uint8_t i = 0, j = 0;

  for(i = 0; i < 7; i++) {
    Tmp_Char = ASCII_NUM_7x6[ChWord-48][i];
    for(j = 0; j < 6; j++) {
      if(((Tmp_Char >> (5 - j)) & 0x01) == 0x01)
        OLED_DrawPixel(CoordiX+j, CoordiY+i, FontColor); // 字符顏色
      else
        OLED_DrawPixel(CoordiX+j, CoordiY+i, BackColor); // 背景顏色
    }
  }
}
void OLED_PutChar_5x7( uint8_t CoordiX, uint8_t CoordiY, int8_t ChWord, uint16_t FontColor, uint16_t BackColor )
{
  uint8_t Tmp_Char = 0;
  uint8_t i = 0, j = 0;

  for(i = 0; i < 5; i++) {
    Tmp_Char = ASCII_NUM_5x7[ChWord-32][i];
    for(j = 0; j < 7; j++) {
      if(((Tmp_Char >> (6 - j)) & 0x01) == 0x01)
        OLED_DrawPixel(CoordiX+i, CoordiY+7-j, FontColor); // 字符顏色
      else
        OLED_DrawPixel(CoordiX+i, CoordiY+7-j, BackColor); // 背景顏色
    }
  }
}

/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_PutStr
**功能 : Put String
**輸入 : CoordiX, CoordiY, ChWord, FontStyle, FontColor, BackColor
**輸出 : None
**使用 : OLED_PutStr(10, 10, (int8_t*)"TFT OLED TEST ... ", WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_PutStr( uint8_t CoordiX, uint8_t CoordiY, int8_t *ChWord, uint16_t FontColor, uint16_t BackColor )
{
  uint16_t OffsetX = 0;

  while(*ChWord) {
    OLED_PutChar(CoordiX+OffsetX, CoordiY, 12, 6, ASCII_12x6[*ChWord], FontColor, BackColor);
    ChWord++;
    OffsetX += 8;
  }
}
void OLED_PutStr_5x7( uint8_t CoordiX, uint8_t CoordiY, int8_t *ChWord, uint16_t FontColor, uint16_t BackColor )
{
  uint16_t OffsetX = 0;

  while(*ChWord) {
    OLED_PutChar_5x7(CoordiX+OffsetX, CoordiY, *ChWord, FontColor, BackColor);
    ChWord++;
    OffsetX += 6;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_PutNum
**功能 : Put Number
**輸入 : oordiX, CoordiY, Type, Length, NumData, FontColor, BackColor
**輸出 : None
**使用 : OLED_PutNum(CoordiX, CoordiY, Type_D, Length, NumData, WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void OLED_PutNum( uint8_t CoordiX, uint8_t CoordiY, StrType Type, uint8_t Length, uint32_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  int8_t TmpNumber[16] = {0};

  Str_NumToChar(Type, Length, TmpNumber, NumData);
  OLED_PutStr(CoordiX, CoordiY, TmpNumber, FontColor, BackColor);
}

void OLED_PutNum_7x6( uint8_t CoordiX, uint8_t CoordiY, uint8_t Length, uint32_t NumData, uint16_t FontColor, uint16_t BackColor )
{
  int8_t TmpNumber[16] = {0};
  int8_t* ChWord = TmpNumber;
  uint16_t OffsetX = 0;

  Str_NumToChar(Type_D, Length, TmpNumber, NumData);

  while(*ChWord) {
    OLED_PutCharNum_7x6(CoordiX+OffsetX, CoordiY, *ChWord, FontColor, BackColor);
    ChWord++;
    OffsetX += 6;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : OLED_TestColoBar
**功能 : Draw Color Bar
**輸入 : None
**輸出 : None
**使用 : OLED_TestColoBar();
**====================================================================================================*/
/*====================================================================================================*/
void OLED_TestColoBar( void )
{
  uint32_t i = 0, j = 0;
  uint16_t drawColor[16] = {
    WHITE,
    RED,
    GREEN,
    BLUE,
    MAGENTA,
    GRED,
    GBLUE,
    BRED,
    BROWN,
    BRRED,
    CYAN,
    GRAY,
    YELLOW,
    DARKBLUE,
    LIGHTBLUE,
    GRAYBLUE
  };

  OLED_SetWindow(0, 0, OLED_W-1, OLED_H-1);

  for(i = 0; i < 16; i++) {
    j = 4 * OLED_W;
    while(j--)
      OLED_WriteColor(drawColor[i]);
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
