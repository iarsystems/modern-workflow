target_include_directories(${PROJECT_NAME} PRIVATE
  ../Inc
)

target_sources(${PROJECT_NAME} PRIVATE
  adc.c
  crc.c
  dac.c
  dma.c
  gpio.c
  led.c
  lights.cpp
  main.cpp
  spi.c
  stm32f429ii_aca.c
  stm32f4xx_hal_msp.c
  stm32f4xx_hal_timebase_tim.c
  stm32f4xx_it.c
  system_stm32f4xx.c
)

add_subdirectory(testcode)