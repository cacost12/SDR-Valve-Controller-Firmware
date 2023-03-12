/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SOL1_Pin GPIO_PIN_2
#define SOL1_GPIO_Port GPIOE
#define SOL2_Pin GPIO_PIN_3
#define SOL2_GPIO_Port GPIOE
#define SOL3_Pin GPIO_PIN_4
#define SOL3_GPIO_Port GPIOE
#define LOX_PG_Pin GPIO_PIN_0
#define LOX_PG_GPIO_Port GPIOC
#define FUEL_PG_Pin GPIO_PIN_1
#define FUEL_PG_GPIO_Port GPIOC
#define SOL4_Pin GPIO_PIN_0
#define SOL4_GPIO_Port GPIOA
#define SOL5_Pin GPIO_PIN_1
#define SOL5_GPIO_Port GPIOA
#define SOL6_Pin GPIO_PIN_2
#define SOL6_GPIO_Port GPIOA
#define STATUS_G_Pin GPIO_PIN_8
#define STATUS_G_GPIO_Port GPIOD
#define STATUS_R_Pin GPIO_PIN_9
#define STATUS_R_GPIO_Port GPIOD
#define STATUS_B_Pin GPIO_PIN_10
#define STATUS_B_GPIO_Port GPIOD
#define USB_DETECT_Pin GPIO_PIN_13
#define USB_DETECT_GPIO_Port GPIOD
#define ENCD2_A_Pin GPIO_PIN_14
#define ENCD2_A_GPIO_Port GPIOD
#define ENCD2_A_EXTI_IRQn EXTI15_10_IRQn
#define ENCD2_B_Pin GPIO_PIN_15
#define ENCD2_B_GPIO_Port GPIOD
#define ENCD2_B_EXTI_IRQn EXTI15_10_IRQn
#define SBV2_DIR_Pin GPIO_PIN_7
#define SBV2_DIR_GPIO_Port GPIOC
#define ENCD1_A_Pin GPIO_PIN_8
#define ENCD1_A_GPIO_Port GPIOC
#define ENCD1_A_EXTI_IRQn EXTI9_5_IRQn
#define ENCD1_B_Pin GPIO_PIN_9
#define ENCD1_B_GPIO_Port GPIOC
#define ENCD1_B_EXTI_IRQn EXTI9_5_IRQn
#define SBV1_EN_Pin GPIO_PIN_8
#define SBV1_EN_GPIO_Port GPIOA
#define SBV2_EN_Pin GPIO_PIN_11
#define SBV2_EN_GPIO_Port GPIOA
#define SBV1_DIR_Pin GPIO_PIN_12
#define SBV1_DIR_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
