/**
  ******************************************************************************
  * @file    stm32f429ii_aca.h
  * @brief   IAR-STM32F429II-ACA Board Support Package (header)
  ******************************************************************************
  * @attention
  *
  * Copyright 2025 (c) IAR Systems AB.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ********
  */

#ifndef __STM32F429II_ACA_BSP__
#define __STM32F429II_ACA_BSP__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define SW1POSn 1
#define SW2POSn 3

typedef struct {
  GPIO_TypeDef * port;
  uint16_t pin;
} GPIO_t;

typedef struct {
  GPIO_TypeDef * port;
  uint16_t pin;
  IRQn_Type irq;
} BUT_t;

typedef enum
{
  LED1 = 0,
  LED2,
  LED3,
  LED4,
  LED5,
  LED6,
  LED7,
  LED8
} LED_e;

typedef enum
{
  BUT1 = 0,
  BUT2,
  BUT3
} BUTTON_e;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI
} BUTTON_m;

typedef enum
{
  SW1_OPEN = GPIO_PIN_RESET,
  SW1_CLOSE = GPIO_PIN_SET
} SW1_e;

typedef enum
{
  SW2_OFF = 1,
  SW2_UNDEF,
  SW2_AUTO = 2,
  SW2_ON = 4
} SW2_e;


void ACA_LED_on(LED_e led);
void ACA_LED_off(LED_e led);
void ACA_LED_toggle(LED_e led);
uint8_t ACA_BUT1_get(void);
uint8_t ACA_BUT2_get(void);
uint8_t ACA_BUT3_get(void);
uint8_t ACA_BUT_get(BUTTON_e button);
SW1_e ACA_SW1_get(void);
SW2_e ACA_SW2_get(void);

#ifdef __cplusplus
}
#endif
#endif /* __STM32F429II_ACA_BSP__ */