# Add the executable target
add_executable(light-effects)

target_include_directories(light-effects PRIVATE
  ${PROJECT_SOURCE_DIR}/inc
)

target_sources(light-effects PRIVATE
  adc.c
  crc.c
  dac.c
  dma.c
  gpio.c
  led.c
  lights.c
  main.c
  spi.c
  stm32f429ii_aca.c
  stm32f4xx_hal_msp.c
  stm32f4xx_hal_timebase_tim.c
  stm32f4xx_it.c
)

# Set the target's compiler options
target_compile_options(light-effects PRIVATE
  $<$<COMPILE_LANGUAGE:C,CXX>:--cpu=cortex-m4 --dlib_config full --no_wrap_diagnostics>
  $<$<COMPILE_LANGUAGE:ASM>:--cpu cortex-m4 -s+>
  --fpu=vfpv4_sp
)

### Add cmsis-device-f4 headers and sources
target_include_directories(light-effects PUBLIC
  ${PROJECT_SOURCE_DIR}/cmsis_6/CMSIS/Core/Include
  ${PROJECT_SOURCE_DIR}/cmsis-device-f4/Include
)
target_sources(light-effects PRIVATE
  ${PROJECT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/startup_stm32f429xx.s
  ${PROJECT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/system_stm32f4xx.c
)

### Add stm32f4xx-hal-driver headers and sources
target_compile_definitions(light-effects PRIVATE
  USE_HAL_DRIVER
  STM32F429xx
)
target_include_directories(light-effects PUBLIC
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Inc
)
target_sources(light-effects PRIVATE
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_adc.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_adc_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_cortex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_crc.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_dac.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_dac_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_dma.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_dma_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_exti.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash_ramfunc.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_gpio.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_pwr.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_pwr_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_rcc.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_rcc_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_spi.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_tim.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_hal_tim_ex.c
  ${PROJECT_SOURCE_DIR}/stm32f4xx-hal-driver/Src/stm32f4xx_ll_adc.c
)

# Set the linker options
target_link_options(light-effects PRIVATE
  --config=${PROJECT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/linker/stm32f429xx_flash.icf
  --map=$<TARGET_FILE_DIR:light-effects>
  --redirect=_Printf=_PrintfFullNoMb
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --fpu=vfpv4_sp
  --semihosting
)

# Generate additional outputs
iar_elftool(light-effects)
