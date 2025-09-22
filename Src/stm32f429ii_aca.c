/**
  ******************************************************************************
  * @file    stm32f429ii_aca.c
  * @brief   IAR-STM32F429II-ACA Board Support Package
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
#include "stm32f4xx_hal.h"

const GPIO_t LED[8] = {
  { LED1_GPIO_Port, LED1_Pin },
  { LED2_GPIO_Port, LED2_Pin },
  { LED3_GPIO_Port, LED3_Pin },
  { LED4_GPIO_Port, LED4_Pin },
  { LED5_GPIO_Port, LED5_Pin },
  { LED6_GPIO_Port, LED6_Pin },
  { LED7_GPIO_Port, LED7_Pin },
  { LED8_GPIO_Port, LED8_Pin } };

const BUT_t BUT[3] = {
  { BUT1_GPIO_Port, BUT1_Pin, BUT1_EXTI_IRQn },
  { BUT2_GPIO_Port, BUT2_Pin, BUT2_EXTI_IRQn },
  { BUT3_GPIO_Port, BUT3_Pin, BUT3_EXTI_IRQn } };

const GPIO_t SW1 = { SW1_CLOSE_GPIO_Port, SW1_CLOSE_Pin };

const GPIO_t SW2[SW2POSn] = {
  { SW2_OFF_GPIO_Port, SW2_OFF_Pin },
  { SW2_AUTO_GPIO_Port, SW2_AUTO_Pin },
  { SW2_ON_GPIO_Port, SW2_ON_Pin } };

/**
  * @brief  Turns on the specified board LED.
  * @param  led Specifies the LED to be toggled.
  * @retval None
  */
void ACA_LED_on(LED_e led)
{
  HAL_GPIO_WritePin(LED[led].port, LED[led].pin, GPIO_PIN_RESET);
}

/**
  * @brief  Turns off the specified board LED.
  * @param  led Specifies the LED to be toggled.
  * @retval None
  */
void ACA_LED_off(LED_e led)
{
  HAL_GPIO_WritePin(LED[led].port, LED[led].pin, GPIO_PIN_SET);
}

/**
  * @brief  Toggles the specified board LED.
  * @param  led Specifies the LED to be toggled.
  * @retval None
  */
void ACA_LED_toggle(LED_e led)
{
  HAL_GPIO_TogglePin(LED[led].port, LED[led].pin);
}

/**
  * @brief  Reads the `Button 1` state.
  * @param  None
  * @retval The input port pin value.
  */
uint8_t ACA_BUT1_get(void)
{
  return HAL_GPIO_ReadPin(BUT[BUT1].port, BUT[BUT1].pin);
}

/**
  * @brief  Reads the `Button 2` state.
  * @param  None
  * @retval The input port pin value.
  */
uint8_t ACA_BUT2_get(void)
{
  return HAL_GPIO_ReadPin(BUT[BUT2].port, BUT[BUT2].pin);
}

/**
  * @brief  Reads the `Button 3` state.
  * @param  None
  * @retval The input port pin value.
  */
uint8_t ACA_BUT3_get(void)
{
  return HAL_GPIO_ReadPin(BUT[BUT3].port, BUT[BUT3].pin);
}

/**
  * @brief  Reads a `Button` state.
  * @param  button
  * @retval The input port pin value.
  */
uint8_t ACA_BUT_get(BUTTON_e button)
{
  return HAL_GPIO_ReadPin(BUT[button].port, BUT[button].pin);
}

/**
  * @brief  Reads `Switch 1` state.
  * @param  None
  * @retval The input port pin value.
  */
SW1_e ACA_SW1_get(void)
{
  GPIO_PinState state = HAL_GPIO_ReadPin(SW1.port, SW1.pin);
  switch(state)
  {
  case GPIO_PIN_RESET:
    return SW1_CLOSE;
  default:
    return SW1_OPEN;
  }
}

/**
  * @brief  Reads the `Switch 2` state.
  * @param  button
  * @retval The input port pin value.
  */
SW2_e ACA_SW2_get(void)
{
  uint32_t state = GPIO_PIN_RESET;

  for(int i = 0; i < SW2POSn; i++)
  {
    state |= !HAL_GPIO_ReadPin(SW2[i].port, SW2[i].pin) << i;
  }
  return (SW2_e)state;
}
