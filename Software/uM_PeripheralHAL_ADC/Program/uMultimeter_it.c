/*====================================================================================================*/
/*====================================================================================================*/
#include "drivers\stm32f3_system.h"
/*====================================================================================================*/
/*====================================================================================================*/
void NMI_Handler( void ) { while(1); }
void HardFault_Handler( void ) { while(1); }
void MemManage_Handler( void ) { while(1); }
void BusFault_Handler( void ) { while(1); }
void UsageFault_Handler( void ) { while(1); }
void SVC_Handler( void ) {}
void DebugMon_Handler( void ) {}
void PendSV_Handler( void ) {}
void SysTick_Handler( void ) { HAL_IncTick(); }
/*====================================================================================================*/
/*====================================================================================================*/
extern ADC_HandleTypeDef ADC_HandleStruct;
/*====================================================================================================*/
/*====================================================================================================*/
//void WWDG_IRQHandler( void )
//void PVD_IRQHandler( void )
//void TAMP_STAMP_IRQHandler( void )
//void RTC_WKUP_IRQHandler( void )
//void FLASH_IRQHandler( void )
//void RCC_IRQHandler( void )
//void EXTI0_IRQHandler( void )
//void EXTI1_IRQHandler( void )
//void EXTI2_TSC_IRQHandler( void )
//void EXTI3_IRQHandler( void )
//void EXTI4_IRQHandler( void )
void DMA1_Channel1_IRQHandler( void )
{
  HAL_DMA_IRQHandler(ADC_HandleStruct.DMA_Handle);
}
//void DMA1_Channel2_IRQHandler( void )
//void DMA1_Channel3_IRQHandler( void )
//void DMA1_Channel4_IRQHandler( void )
//void DMA1_Channel5_IRQHandler( void )
//void DMA1_Channel6_IRQHandler( void )
//void DMA1_Channel7_IRQHandler( void )
void ADC1_2_IRQHandler( void )
{
  HAL_ADC_IRQHandler(&ADC_HandleStruct);
}
//void CAN_TX_IRQHandler( void )
//void CAN_RX0_IRQHandler( void )
//void CAN_RX1_IRQHandler( void )
//void CAN_SCE_IRQHandler( void )
//void EXTI9_5_IRQHandler( void )
//void TIM1_BRK_TIM15_IRQHandler( void )
//void TIM1_UP_TIM16_IRQHandler( void )
//void TIM1_TRG_COM_TIM17_IRQHandler( void )
//void TIM1_CC_IRQHandler( void )
//void TIM2_IRQHandler( void )
//void TIM3_IRQHandler( void )
//void I2C1_EV_IRQHandler( void )
//void I2C1_ER_IRQHandler( void )
//void SPI1_IRQHandler( void )
//void USART1_IRQHandler( void )
//void USART2_IRQHandler( void )
//void USART3_IRQHandler( void )
//void EXTI15_10_IRQHandler( void )
//void RTC_Alarm_IRQHandler( void )
//void TIM6_DAC1_IRQHandler( void )
//void TIM7_DAC2_IRQHandler( void )
//void COMP2_IRQHandler( void )
//void COMP4_6_IRQHandler( void )
//void FPU_IRQHandler( void )
/*====================================================================================================*/
/*====================================================================================================*/
