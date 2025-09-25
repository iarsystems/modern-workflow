/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#pragma cstat_disable="CERT-MSC41-C_b","CERT-INT36-C","CERT-INT31-C_a"
#include "stm32f4xx_hal.h"
#pragma cstat_restore="CERT-MSC41-C_b","CERT-INT36-C","CERT-INT31-C_a"
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
#define SW2_OFF_Pin GPIO_PIN_8
#define SW2_OFF_GPIO_Port GPIOI
#define BUT2_Pin GPIO_PIN_13
#define BUT2_GPIO_Port GPIOC
#define BUT2_EXTI_IRQn EXTI15_10_IRQn
#define SW2_AUTO_Pin GPIO_PIN_9
#define SW2_AUTO_GPIO_Port GPIOI
#define SW2_ON_Pin GPIO_PIN_10
#define SW2_ON_GPIO_Port GPIOI
#define SW1_CLOSE_Pin GPIO_PIN_11
#define SW1_CLOSE_GPIO_Port GPIOI
#define SPI_FLASH_NSS_Pin GPIO_PIN_6
#define SPI_FLASH_NSS_GPIO_Port GPIOF
#define SPI_FLASH_CLK_Pin GPIO_PIN_7
#define SPI_FLASH_CLK_GPIO_Port GPIOF
#define SPI_FLASH_MISO_Pin GPIO_PIN_8
#define SPI_FLASH_MISO_GPIO_Port GPIOF
#define SPI_FLASH_MOSI_Pin GPIO_PIN_9
#define SPI_FLASH_MOSI_GPIO_Port GPIOF
#define BUT1_Pin GPIO_PIN_0
#define BUT1_GPIO_Port GPIOA
#define BUT1_EXTI_IRQn EXTI0_IRQn
#define SYNC_Pin GPIO_PIN_1
#define SYNC_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_4
#define LED1_GPIO_Port GPIOA
#define SPEAKER_Pin GPIO_PIN_5
#define SPEAKER_GPIO_Port GPIOA
#define TRIMMER_Pin GPIO_PIN_6
#define TRIMMER_GPIO_Port GPIOA
#define CAP_BUT1_Pin GPIO_PIN_6
#define CAP_BUT1_GPIO_Port GPIOH
#define CAP_BUT1_EXTI_IRQn EXTI9_5_IRQn
#define CAP_BUT2_Pin GPIO_PIN_7
#define CAP_BUT2_GPIO_Port GPIOH
#define CAP_BUT2_EXTI_IRQn EXTI9_5_IRQn
#define OTG_HS_DM_Pin GPIO_PIN_14
#define OTG_HS_DM_GPIO_Port GPIOB
#define OTG_HS_DP_Pin GPIO_PIN_15
#define OTG_HS_DP_GPIO_Port GPIOB
#define LED6_Pin GPIO_PIN_11
#define LED6_GPIO_Port GPIOD
#define LED7_Pin GPIO_PIN_12
#define LED7_GPIO_Port GPIOD
#define LED8_Pin GPIO_PIN_13
#define LED8_GPIO_Port GPIOD
#define LED2_Pin GPIO_PIN_4
#define LED2_GPIO_Port GPIOD
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOD
#define LED4_Pin GPIO_PIN_6
#define LED4_GPIO_Port GPIOD
#define LED5_Pin GPIO_PIN_7
#define LED5_GPIO_Port GPIOD
#define BUT3_Pin GPIO_PIN_9
#define BUT3_GPIO_Port GPIOG
#define BUT3_EXTI_IRQn EXTI9_5_IRQn
#define OTG_HS_VBUSON_Pin GPIO_PIN_5
#define OTG_HS_VBUSON_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
