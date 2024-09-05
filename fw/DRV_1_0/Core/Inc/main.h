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
#include "stm32g0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_ERROR_Pin GPIO_PIN_13
#define LED_ERROR_GPIO_Port GPIOC
#define LED_PROCESS_Pin GPIO_PIN_14
#define LED_PROCESS_GPIO_Port GPIOC
#define LED_OK_Pin GPIO_PIN_15
#define LED_OK_GPIO_Port GPIOC
#define ADDR0_Pin GPIO_PIN_0
#define ADDR0_GPIO_Port GPIOA
#define ADDR1_Pin GPIO_PIN_1
#define ADDR1_GPIO_Port GPIOA
#define UART2_CS0_Pin GPIO_PIN_4
#define UART2_CS0_GPIO_Port GPIOA
#define SPI_CS0_Pin GPIO_PIN_0
#define SPI_CS0_GPIO_Port GPIOB
#define SPI_CS1_Pin GPIO_PIN_1
#define SPI_CS1_GPIO_Port GPIOB
#define ADDR2_Pin GPIO_PIN_2
#define ADDR2_GPIO_Port GPIOB
#define UART3_CS0_Pin GPIO_PIN_12
#define UART3_CS0_GPIO_Port GPIOB
#define LS0_Pin GPIO_PIN_15
#define LS0_GPIO_Port GPIOB
#define LS1_Pin GPIO_PIN_8
#define LS1_GPIO_Port GPIOA
#define LS2_Pin GPIO_PIN_9
#define LS2_GPIO_Port GPIOA
#define LS3_Pin GPIO_PIN_6
#define LS3_GPIO_Port GPIOC
#define LS4_Pin GPIO_PIN_7
#define LS4_GPIO_Port GPIOC
#define LS5_Pin GPIO_PIN_10
#define LS5_GPIO_Port GPIOA
#define BUZZ_Pin GPIO_PIN_15
#define BUZZ_GPIO_Port GPIOA
#define UART5_CS0_Pin GPIO_PIN_3
#define UART5_CS0_GPIO_Port GPIOB
#define BOOT_BTN_Pin GPIO_PIN_4
#define BOOT_BTN_GPIO_Port GPIOB
#define UART6_CS0_Pin GPIO_PIN_7
#define UART6_CS0_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
