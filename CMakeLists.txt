cmake_minimum_required(VERSION 3.31)

# Project-specific CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(iar-tools)

# Configure a CMake project
project(light-effects)
enable_language(ASM)
enable_testing()

# Add the executable target
add_executable(${PROJECT_NAME})

# Set the target's compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<COMPILE_LANGUAGE:C,CXX>:--dlib_config full --no_wrap_diagnostics -e>
  $<$<COMPILE_LANGUAGE:ASM>:-s+>
  --cpu=cortex-m4
  --fpu=vfpv4_sp
)

### Add cmsis-device-f4 headers and sources
target_include_directories(${PROJECT_NAME} PUBLIC
  cmsis_6/CMSIS/Core/Include
  cmsis-device-f4/Include
)
target_sources(${PROJECT_NAME} PRIVATE
  cmsis-device-f4/Source/Templates/iar/startup_stm32f429xx.s
  cmsis-device-f4/Source/Templates/system_stm32f4xx.c
)

### Add stm32f4xx-hal-driver headers and sources
target_compile_definitions(${PROJECT_NAME} PRIVATE
  USE_HAL_DRIVER
  STM32F429xx
)
target_include_directories(${PROJECT_NAME} PUBLIC
  stm32f4xx-hal-driver/Inc
)
target_sources(${PROJECT_NAME} PRIVATE
  stm32f4xx-hal-driver/Src/stm32f4xx_hal.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_adc.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_adc_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_cortex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_crc.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_dac.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_dac_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_dma.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_dma_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_exti.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_flash_ramfunc.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_gpio.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_pwr.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_pwr_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_rcc.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_rcc_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_spi.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_tim.c
  stm32f4xx-hal-driver/Src/stm32f4xx_hal_tim_ex.c
  stm32f4xx-hal-driver/Src/stm32f4xx_ll_adc.c
)

# Add application's sources
add_subdirectory(src)
add_subdirectory(lib)

# Set the linker options
target_link_options(${PROJECT_NAME} PRIVATE
  --config=${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/linker/stm32f429xx_flash.icf
  --map=${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/$<TARGET_PROPERTY:NAME>.map
  --redirect=_Printf=_PrintfFullNoMb
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --fpu=vfpv4_sp
  --semihosting
  --vfe
)

# Generate additional outputs
iar_elftool(${PROJECT_NAME})

# Touch `build/DartConfiguration.tcl` (not used)
# for supressing CMake Tools warning about 
# missing file during during CTest
file(TOUCH ${CMAKE_BINARY_DIR}/DartConfiguration.tcl)