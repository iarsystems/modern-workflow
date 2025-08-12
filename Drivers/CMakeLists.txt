target_include_directories(${PROJECT_NAME} PUBLIC
  CMSIS/Include
  CMSIS/Device/ST/STM32F4xx/Include
  STM32F4xx_HAL_Driver/Inc
  STM32F4xx_HAL_Driver/Inc/Legacy
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  USE_HAL_DRIVER
  STM32F429xx
)

target_sources(${PROJECT_NAME} PRIVATE
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_adc_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_crc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dac_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_spi.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
  STM32F4xx_HAL_Driver/Src/stm32f4xx_ll_adc.c
)