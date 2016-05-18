/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"

#include "uMultimeter.h"
#include "uMultimeter_ui.h"
#include "uMultimeter_probe.h"
#include "uMultimeter_expand.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define EXPAND_PROBEA_SW_PIN      GPIO_Pin_6
#define EXPAND_PROBEA_SW_PORT     GPIOA
#define EXPAND_PROBEA_SW_Set()    __GPIO_SET(EXPAND_PROBEA_SW_PORT, EXPAND_PROBEA_SW_PIN)
#define EXPAND_PROBEA_SW_Reset()  __GPIO_RST(EXPAND_PROBEA_SW_PORT, EXPAND_PROBEA_SW_PIN)
/*====================================================================================================*/
/*====================================================================================================*
**函數 : UM_PROBE_Config
**功能 : Probe Config
**輸入 : None
**輸出 : None
**使用 : UM_PROBE_Config();
**====================================================================================================*/
/*====================================================================================================*/
void UM_PROBE_modeVOL( FunctionalState state )
{
  GPIO_InitTypeDef GPIO_InitStruct;

  if(state == ENABLE) {
    GPIO_InitStruct.GPIO_Pin   = EXPAND_PROBEA_SW_PIN;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(EXPAND_PROBEA_SW_PORT, &GPIO_InitStruct);
  }
  else {
    GPIO_InitStruct.GPIO_Pin   = EXPAND_PROBEA_SW_PIN;
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(EXPAND_PROBEA_SW_PORT, &GPIO_InitStruct);
  }
}

void UM_EXPAND_modeInit( uint32_t mode )
{
  switch(mode) {
    case MODE_VOL:
      UM_PROBE_modeVOL(ENABLE);
      break;
    case MODE_RES:
      UM_PROBE_modeVOL(ENABLE);
      EXPAND_PROBEA_SW_Set();
      break;
    case MODE_PWM:
      UM_PROBE_modeVOL(DISABLE);
      break;
    case MODE_WAV:
      UM_PROBE_modeVOL(DISABLE);
      break;
    case MODE_EXP:
      UM_PROBE_modeVOL(DISABLE);
      break;
  }
}

void UM_EXPAND_modeVol( uint32_t mode )
{
  switch(mode) {
    case MODE_VOL_CH1:
      EXPAND_PROBEA_SW_Set();
      break;
    case MODE_VOL_CH2:
      EXPAND_PROBEA_SW_Reset();
      break;
    case MODE_VOL_DIF:
      EXPAND_PROBEA_SW_Reset();
      break;
  }
}
/*====================================================================================================*/
/*====================================================================================================*/
