/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
* 		stm32h7xx_it.c                                                           *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Basic interrupt service routines for STM32H750 MCU                       *
*                                                                              *
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"

/* Project Includes */
#include "valve.h"
#include "sdr_pin_defines_L0005.h"


/*******************************************************************************
*           Cortex Processor Interruption and Exception Handlers               *
*******************************************************************************/

/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		EXTI9_5_IRQHandler                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*     This function handles EXTI line[9:5] interrupts. Calls the valve encoder *
*     ISRs depending on which pin generated the interrupt                      *
*                                                                              *
*******************************************************************************/
void EXTI9_5_IRQHandler
  ( 
  void 
  )
{
/* LOX Encoder A Signal interrupt */
if ( __HAL_GPIO_EXTI_GET_FLAG( LOX_ENC_A_PIN ) )
    {
    __HAL_GPIO_EXTI_CLEAR_FLAG( LOX_ENC_A_PIN );
    lox_channelA_ISR(); 
    }

/* LOX Encoder B Signal interrupt */
if ( __HAL_GPIO_EXTI_GET_FLAG( LOX_ENC_B_PIN ) )
    {
    __HAL_GPIO_EXTI_CLEAR_FLAG( LOX_ENC_B_PIN );
    lox_channelB_ISR(); 
    }

/* Fuel Encoder A Signal Interrupt */
if ( __HAL_GPIO_EXTI_GET_FLAG( KER_ENC_A_PIN ) )
    {
    __HAL_GPIO_EXTI_CLEAR_FLAG( KER_ENC_A_PIN );
    fuel_channelA_ISR();
    }
} /* EXTI9_5_IRQHandler */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		EXTI15_10_IRQHandler                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
*     This function handles EXTI line[15:10] interrupts. Calls the valve       *
*     encoder ISRs depending on which pin generated the interrupt              *
*                                                                              *
*******************************************************************************/
void EXTI15_10_IRQHandler
    (
    void
    )
{
__HAL_GPIO_EXTI_CLEAR_FLAG( KER_ENC_B_PIN );
fuel_channelB_ISR();
} /* EXTI15_10_IRQHandler */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/