target_sources(driver PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    stm32f4xx_hal.c
    stm32f4xx_hal_adc.c
    stm32f4xx_hal_adc_ex.c
    stm32f4xx_hal_cortex.c
    stm32f4xx_hal_crc.c
    stm32f4xx_hal_dac.c
    stm32f4xx_hal_dac_ex.c
    stm32f4xx_hal_dma.c
    stm32f4xx_hal_dma_ex.c
    stm32f4xx_hal_exti.c
    stm32f4xx_hal_flash.c
    stm32f4xx_hal_flash_ex.c
    stm32f4xx_hal_flash_ramfunc.c
    stm32f4xx_hal_gpio.c
    stm32f4xx_hal_pwr.c
    stm32f4xx_hal_pwr_ex.c
    stm32f4xx_hal_rcc.c
    stm32f4xx_hal_rcc_ex.c
    stm32f4xx_hal_spi.c
    stm32f4xx_hal_tim.c
    stm32f4xx_hal_tim_ex.c
    stm32f4xx_ll_adc.c
)

set_property(FILE_SET skip_lint TARGET driver PROPERTY SKIP_LINTING ON)
