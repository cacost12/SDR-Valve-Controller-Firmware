/*******************************************************************************
*                                                                              *
* FILE:                                                                        *
*       stm32h7xx_hal_msp.c                                                    *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Contains implementation of MSP initialization and de-initialization    *
*                routines                                                      *
*                                                                              *
*******************************************************************************/

/*------------------------------------------------------------------------------
 Standard Includes                                                              
------------------------------------------------------------------------------*/
#include "main.h"

/*------------------------------------------------------------------------------
 Function Prototypes 
------------------------------------------------------------------------------*/

/* TIM Post MSP Initialization */
void HAL_TIM_MspPostInit
    (
    TIM_HandleTypeDef *htim
    );


/*------------------------------------------------------------------------------
 Procedures 
------------------------------------------------------------------------------*/

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_MspInit                                                            *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the Global MSP                                             *
*                                                                              *
*******************************************************************************/
void HAL_MspInit
    (
    void
    )
{
__HAL_RCC_SYSCFG_CLK_ENABLE();
} /* HAL_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_TIM_BASE_MspInit                                                   *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the base timer MSP                                         *
*                                                                              *
*******************************************************************************/
void HAL_TIM_Base_MspInit
    (
    TIM_HandleTypeDef* htim_base
    )
{
if( htim_base->Instance == TIM15 )
    {
    /* Peripheral clock enable */
    __HAL_RCC_TIM15_CLK_ENABLE();
    }
} /* HAL_TIM_Base_MspInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_TIM_MspPostInit                                                    *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Timer Post MSP Initialization                                          *
*                                                                              *
*******************************************************************************/
void HAL_TIM_MspPostInit
    (
    TIM_HandleTypeDef* htim
    )
{
GPIO_InitTypeDef GPIO_InitStruct = {0};
if( htim->Instance == TIM15 )
    {
    /* GPIO Clock Enable */
    __HAL_RCC_GPIOE_CLK_ENABLE();

    /* TIM15 GPIO Configuration
    PE5     ------> TIM15_CH1
    PE6     ------> TIM15_CH2 */
    GPIO_InitStruct.Pin       = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF4_TIM15;
    HAL_GPIO_Init( GPIOE, &GPIO_InitStruct );
    }

} /* HAL_TIM_MspPostInit */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_TIM_Base_MspDeInit                                                 *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Base Timer MSP Deinitialization                                        *
*                                                                              *
*******************************************************************************/
void HAL_TIM_Base_MspDeInit
    (
    TIM_HandleTypeDef* htim_base
    )
{
if( htim_base->Instance == TIM15 )
    {
    /* Peripheral clock disable */
    __HAL_RCC_TIM15_CLK_DISABLE();
    }
} /* HAL_TIM_Base_MspDeInit */
 

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspInit                                                       *
*                                                                              *
* DESCRIPTION:                                                                 *
*       Initializes the UART MSP                                               *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspInit
    (
    UART_HandleTypeDef* huart
    )
{
/* Initialization Structs */
GPIO_InitTypeDef         GPIO_InitStruct     = {0};
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

/* USB UART Initialization */
if( huart->Instance == USART3 )
    {
    /* Initializes the peripherals clock */
    PeriphClkInitStruct.PeriphClockSelection      = RCC_PERIPHCLK_USART3;
    PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
    if ( HAL_RCCEx_PeriphCLKConfig( &PeriphClkInitStruct ) != HAL_OK )
        {
        Error_Handler();
        }

    /* Peripheral clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    /* USART3 GPIO Configuration
      PC10     ------> USART3_TX
      PC11     ------> USART3_RX */
    GPIO_InitStruct.Pin       = GPIO_PIN_10 | GPIO_PIN_11;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_NOPULL;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init( GPIOC, &GPIO_InitStruct );
    }
} /* HAL_UART_MspInit */
 

/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
*       HAL_UART_MspDeInit                                                     *
*                                                                              *
* DESCRIPTION:                                                                 *
*       De-Initializes the UART MSP                                            *
*                                                                              *
*******************************************************************************/
void HAL_UART_MspDeInit
    (
    UART_HandleTypeDef* huart
    )
{
/* USB UART De-initialization */
if( huart->Instance == USART3 )
    {
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /* USART3 GPIO Configuration
       PA10     ------> USART3_TX
       PA11     ------> USART3_RX */
    HAL_GPIO_DeInit( GPIOC, GPIO_PIN_10 | GPIO_PIN_11 );
    }
} /* HAL_UART_MspDeInit */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/