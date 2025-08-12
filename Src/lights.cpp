/**
  ******************************************************************************
  * @file    lights.c
  * @brief   IAR-STM32F429II-ACA Light Effects
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

#include "stm32f429ii_aca.h"
#include "test_config.h"
#include "led.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"

/**
  * @brief  Generate a mask for light effects.
  * @param  None
  * @retval The LED mask value.
  */
uint8_t generateMaskEffect(void)
{
  const char *av_override[] = {"exe", "-v", "-ojunit"}; // verbose mode on
  const uint8_t effect_speed = 1;
  static uint8_t n = 0;
  static uint8_t led_mask = 0;

  /* Check `Switch 2` state */
  switch (ACA_SW2_get())
  {
  case SW2_AUTO:
    led_mask = 1 << (n++ % 8);
    break;
  case SW2_OFF:
    led_mask = (n++ & 2) ? 1 : 0;
    CommandLineTestRunner::RunAllTests(2, (char **)av_override);
    break;
  case SW2_ON:
    switch ((n++ & (3 << effect_speed)) >> effect_speed)
    {
    case 0:
      led_mask = 0b01010101;           // 0x5A
      break;
    case 1:
      led_mask = 0b01011010;           // 0x55
      break;
    case 2:
      led_mask = 0b10101010;           // 0xAA;
      break;
    case 3:
      led_mask = 0b10100101;           // 0xA5;
      break;
    }
    break;
  default:
    led_mask = 0;
  }

  /* Check `Switch 1` state */
  switch (ACA_SW1_get())
  {
  case SW1_OPEN:
    (void)led_mask;
    break;
  case SW1_CLOSE:
    led_mask = ~led_mask;
    break;
  default:
    led_mask = 0;
  }

  return led_mask;
}

/**
  * @brief  The main demo.
  * @param  None
  * @retval None
  */
void lights(void)
{
  uint8_t led_mask = generateMaskEffect();
  blink(&led_mask);
  HAL_Delay(200); // ms
}