/*====================================================================================================*/
/*====================================================================================================*/
#include "stm32f1_system.h"
#include "stm32f1_adc.h"
#include "stm32f1_usb.h"
#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "uMultimeter_measure.h"
#include "api_waveForm.h"
#include "module_buzzer.h"
#include "module_ssd1331.h"
#include "algorithm_mathUnit.h"

#include "exp_digiGPIO.h"
#include "exp_digiPower.h"
#include "exp_tachometer.h"
#include "exp_imu.h"
/*====================================================================================================*/
/*====================================================================================================*/
WaveForm_Struct WaveForm;
/*====================================================================================================*/
/*====================================================================================================*
**函數 : GPIO_Config
**功能 : LED and KEY Config
**輸入 : None
**輸出 : None
**使用 : GPIO_Config();
**====================================================================================================*/
/*====================================================================================================*/
static void GPIO_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Clk Init *************************************************************/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  /* LED Config */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /* KEY Config */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_R_Set;
  LED_G_Set;
  LED_B_Set;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_SystemInit
**功能 : uMultimeter Init
**輸入 : None
**輸出 : None
**使用 : uMultimeter_SystemInit();
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_SystemInit( void )
{
  GPIO_Config();
  Buzzer_Config();
  SSD1331_Config();
  Probe_Config();

  ExpIO_Init();

  USB_InitVCP();

  Buzzer_setLoudness(60);
  SSD1331_Init();

	WaveForm.Channel = 2;
	WaveForm.WindowColor = WHITE;
	WaveForm.BackColor = BLACK;
	WaveForm.Data[0] = 0;
	WaveForm.Data[1] = 0;
	WaveForm.Scale[0] = 100;
	WaveForm.Scale[1] = 100;
	WaveForm.PointColor[0] = GREEN;
	WaveForm.PointColor[1] = BLUE;

  OLED_Clear(BLACK);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_measureMode_Init
**功能 : 
**輸入 : mode, modeS
**輸出 : None
**使用 : uMultimeter_measureMode(mode, modeS);
**====================================================================================================*/
/*====================================================================================================*/
void modeVOL_Init( uint32_t mode );
void modeVOL_CH1( void );
void modeVOL_CH2( void );
void modeVOL_DIF( void );

void modeRES_Init( uint32_t mode );
void modeRES_RES( void );
void modeRES_DIO( void );

void modePWM_Init( uint32_t mode );
void modePWM_OUT( void );
void modePWM_IN( void );

void modeWAV_Init( uint32_t mode );
void modeWAV_CH1( void );
void modeWAV_CH2( void );
void modeWAV_ALL( void );
void modeWAV_EXP( void );

void modeEXP_Init( uint32_t mode );
void modeEXP_NUL( void );

struct menuItem_st itemVOL[MODE_VOL_MAX] = {
  {MODE_VOL_CH1, &modeVOL_CH1},
  {MODE_VOL_CH2, &modeVOL_CH2},
  {MODE_VOL_DIF, &modeVOL_DIF},
};
struct menuItem_st itemRES[MODE_RES_MAX] = {
  {MODE_RES_RES, &modeRES_RES},
  {MODE_RES_DIO, &modeRES_DIO},
};
struct menuItem_st itemPWM[MODE_PWM_MAX] = {
  {MODE_PWM_OUT, &modePWM_OUT},
  {MODE_PWM_IN,  &modePWM_IN},
};
struct menuItem_st itemWAV[MODE_WAV_MAX] = {
  {MODE_WAV_CH1, &modeWAV_CH1},
  {MODE_WAV_CH2, &modeWAV_CH2},
  {MODE_WAV_ALL, &modeWAV_ALL},
  {MODE_WAV_EXP, &modeWAV_EXP},
};
struct menuItem_st itemEXP[MODE_EXP_MAX] = {
  {MODE_EXP_NUL,  &modeEXP_NUL},
  {MODE_EXP_POW,  &modeEXP_POW},
//  {MODE_EXP_POT,  &modeEXP_POT},
//  {MODE_EXP_CUR,  &modeEXP_CUR},
//  {MODE_EXP_ADC,  &modeEXP_ADC},
//  {MODE_EXP_DAC,  &modeEXP_DAC},
//  {MODE_EXP_MOI,  &modeEXP_MOI},
  {MODE_EXP_ROT,  &modeEXP_ROT},
//  {MODE_EXP_MAG,  &modeEXP_MAG},
  {MODE_EXP_IMU,  &modeEXP_IMU},
//  {MODE_EXP_BMP,  &modeEXP_BMP},
//  {MODE_EXP_TEMP, &modeEXP_TEMP},
//  {MODE_EXP_RFLW, &modeEXP_RFLW},
};
struct menuPage_st menuPage[MODE_BDR_MAX] = {
  {MODE_VOL_DIF, 0, itemVOL, MODE_VOL_MAX, modeVOL_Init},
  {MODE_RES_RES, 0, itemRES, MODE_RES_MAX, modeRES_Init},
  {MODE_PWM_OUT, 0, itemPWM, MODE_PWM_MAX, modePWM_Init},
  {MODE_WAV_ALL, 0, itemWAV, MODE_WAV_MAX, modeWAV_Init},
  {MODE_EXP_NUL, 0, itemEXP, MODE_EXP_MAX, modeEXP_Init},
};
struct menuPage_st topPage = {DEFAULT_MODE, menuPage, 0, 0, uMultimeterUI_menuDisplay};

void modeVOL_Init( uint32_t mode )
{
  ProbeOCH_OutputEN(0, DISABLE);
  ProbeOCH_OutputEN(1, DISABLE);
  uMultimeterUI_modeVOL_Init(mode);
  itemVOL[mode].pFunc();
}
void modeVOL_CH1( void )
{
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  tmpData = uMultimeter_measure_ADCtoVol(readData[0]);
  uMultimeterUI_modeVOL(readData[0], readData[1], tmpData);

  USB_VCP_SendStr((uint8_t *)"Vol = ");
  USB_VCP_SendNum(Type_D, 5, tmpData);
  USB_VCP_SendStr((uint8_t *)" mV\r\n");
}
void modeVOL_CH2( void )
{
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  tmpData = uMultimeter_measure_ADCtoVol(readData[1]);
  uMultimeterUI_modeVOL(readData[0], readData[1], tmpData);

  USB_VCP_SendStr((uint8_t *)"Vol = ");
  USB_VCP_SendNum(Type_D, 5, tmpData);
  USB_VCP_SendStr((uint8_t *)" mV\r\n");
}
void modeVOL_DIF( void )
{
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  tmpData = (readData[0] > readData[1]) ? uMultimeter_measure_ADCtoVol(readData[0] - readData[1]) : uMultimeter_measure_ADCtoVol(readData[1] - readData[0]);
  uMultimeterUI_modeVOL(readData[0], readData[1], tmpData);

  USB_VCP_SendStr((uint8_t *)"Vol = ");
  USB_VCP_SendNum(Type_D, 5, tmpData);
  USB_VCP_SendStr((uint8_t *)" mV\r\n");
}

void modeRES_Init( uint32_t mode )
{
  ProbeOCH_OutputEN(0, ENABLE);
  ProbeOCH_OutputEN(1, DISABLE);
  uMultimeterUI_modeRES_Init(mode);
  itemRES[mode].pFunc();
}
void modeRES_RES( void )
{
  uint8_t state = 0;
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  state = Buzzer_cmp(readData[0], 50);
  tmpData = uMultimeter_measure_ADCtoRes(readData[0]);
  uMultimeterUI_modeRES_RES(tmpData, state);
}
void modeRES_DIO( void )
{
  uint8_t state = 0;
  uint32_t tmpData = 0;
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  state = Buzzer_cmp(readData[0], 50);
  tmpData = uMultimeter_measure_ADCtoVol(readData[0]);
  uMultimeterUI_modeRES_DIO(tmpData, state);
}

void modePWM_Init( uint32_t mode )
{
  ProbeOCH_OutputEN(0, ENABLE);
  ProbeOCH_OutputEN(1, DISABLE);
  uMultimeterUI_modePWM_Init(mode);
  itemPWM[mode].pFunc();
}
void modePWM_OUT( void )
{
//  ProbeOCH_SetDuty(2000);

  // DEMO MODE
  static uint8_t satae = 0;
  static uint16_t i = 0;

  i = satae ? i - 50 : i + 50;
  if(i == 10000)  satae = 1;
  if(i == 0)      satae = 0;

  ProbeOCH_SetDuty(i);

  uMultimeterUI_modePWM(ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
}
void modePWM_IN( void )
{
  uMultimeterUI_modePWM(ProbeOCH_GetDuty(), ProbeOCH_GetFreq());
}

void modeWAV_Init( uint32_t mode )
{
  ProbeOCH_OutputEN(0, DISABLE);
  ProbeOCH_OutputEN(1, DISABLE);
  uMultimeterUI_modeWAV_Init(mode);
  itemWAV[mode].pFunc();
}
void modeWAV_CH1( void )
{
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
  WaveForm.Data[1] = uMultimeter_measure_ADCtoVol(readData[1]);
  uMultimeterUI_modeWAV_CH1(&WaveForm);
}
void modeWAV_CH2( void )
{
//  uint32_t readData[2] = {0};

//  readData[0] = ProbeICH_ReadAveADC(0);
//  readData[1] = ProbeICH_ReadAveADC(1);
//  WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
//  WaveForm.Data[1] = uMultimeter_measure_ADCtoVol(readData[1]);
//  uMultimeterUI_modeWAV_CH2(&WaveForm);

  // DEMO MODE
  uint32_t readData[2] = {0};
  static int32_t theta = 0;

  theta += 2;
  if(theta == 180) theta = 0;

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
  WaveForm.Data[1] = arm_sin_f32(toRad(theta)) * 4600;
  uMultimeterUI_modeWAV_CH2(&WaveForm);
}
void modeWAV_ALL( void )
{
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
  WaveForm.Data[1] = uMultimeter_measure_ADCtoVol(readData[1]);
  uMultimeterUI_modeWAV_ALL(&WaveForm);
}
void modeWAV_EXP( void )
{
  uint32_t readData[2] = {0};

  readData[0] = ProbeICH_ReadAveADC(0);
  readData[1] = ProbeICH_ReadAveADC(1);
  WaveForm.Data[0] = uMultimeter_measure_ADCtoVol(readData[0]);
  WaveForm.Data[1] = uMultimeter_measure_ADCtoVol(readData[1]);
  uMultimeterUI_modeWAV_ALL(&WaveForm);
}

void modeEXP_Init( uint32_t mode )
{
  ProbeOCH_OutputEN(0, DISABLE);
  ProbeOCH_OutputEN(1, DISABLE);
  uMultimeterUI_modeEXP_Init(mode);

  switch(mode) {
    case MODE_EXP_NUL:  break;
    case MODE_EXP_POW:  ExpPOW_Init();  break;
//    case MODE_EXP_POT:  break;
//    case MODE_EXP_CUR:  break;
//    case MODE_EXP_ADC:  break;
//    case MODE_EXP_DAC:  break;
//    case MODE_EXP_MOI:  break;
    case MODE_EXP_ROT:  ExpROT_Init();  break;
//    case MODE_EXP_MAG:  break;
    case MODE_EXP_IMU:  ExpIMU_Init();  break;
//    case MODE_EXP_MIC:  break;
//    case MODE_EXP_BMP:  break;
//    case MODE_EXP_TEMP: break;
//    case MODE_EXP_RFLW: break;
    default:            break;
  }

  itemEXP[mode].pFunc();
}
void modeEXP_NUL( void )
{
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter_expandMode
**功能 : 
**輸入 : None
**輸出 : None
**使用 : 
**====================================================================================================*/
/*====================================================================================================*/
void uMultimeter_expandMode( void )
{
  static uint8_t expandState = 0;

  if(expandState != ExpIO_getExpID()) {
    expandState = ExpIO_getExpID();
    switch(expandState) {
      case 0x00:  // [0, 0] -> AD
        topPage.mode = MODE_VOL;
        break;
      case 0x01:  // [0, 1] -> SPI
        topPage.mode = MODE_EXP;
        break;
      case 0x02:  // [1, 0] -> I2C
        topPage.mode = MODE_EXP;
        break;
      case 0x03:  // [1, 1] -> IO
        topPage.mode = MODE_EXP;
        break;
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : uMultimeter
**功能 : 
**輸入 : None
**輸出 : None
**使用 : uMultimeter();
**====================================================================================================*/
/*====================================================================================================*/
#define DeBounce 20
void uMultimeter( void )
{
  static int8_t updateState = 1;  // 1 - Update, 0 - No Update
  static int8_t modeState_selNew = DEFAULT_MODE;
  static int8_t modeState_selOld = MODE_BDR_MIN;

  if(KEY_R_Read) {
    modeState_selNew++;
    if(modeState_selNew == MODE_BDR_MAX)
      modeState_selNew = MODE_BDR_MIN + 1;
    Delay_10ms(DeBounce);
  }
  if(KEY_L_Read) {
    modeState_selNew--;
    if(modeState_selNew == MODE_BDR_MIN)
      modeState_selNew = MODE_BDR_MAX - 1;
    Delay_10ms(DeBounce);
  }
  if(KEY_P_Read) {
    if(modeState_selOld == modeState_selNew) {
      topPage.pPage[topPage.mode].mode++;
      if(topPage.pPage[topPage.mode].mode == topPage.pPage[topPage.mode].itemNum)
        topPage.pPage[topPage.mode].mode = 0;
      updateState = 1;
    }
    topPage.mode = modeState_selNew;
    Delay_10ms(DeBounce);
  }

  topPage.Init(Byte16(uint32_t, modeState_selNew, topPage.pPage[topPage.mode].mode));

  if((modeState_selOld != topPage.mode) || updateState) {
    modeState_selOld = topPage.mode;
    updateState = 0;
    Buzzer_cmd(DISABLE);
    menuPage[topPage.mode].Init(topPage.pPage[modeState_selNew].mode);  // init
  }
  else {
    menuPage[topPage.mode].pItem[menuPage[topPage.mode].mode].pFunc(); // run
  }

  uMultimeter_expandMode();
}
/*====================================================================================================*/
/*====================================================================================================*/
