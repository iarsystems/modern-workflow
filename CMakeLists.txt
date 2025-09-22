# This CMake project uses CMake v4.1+
cmake_minimum_required(VERSION 4.1)

# Set CMake for cross-compiling
set(CMAKE_SYSTEM_NAME Generic)

# Enable all CMake configuration types
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo MinSizeRel)

# Include `./cmake` to the CMake's module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Declare a CMake project
project(light-effects)
enable_language(ASM)

# Add the executable target
add_executable(${PROJECT_NAME})

# Enable IAR C-STAT Static Analysis
#set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
#set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")

# Set the target's compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<COMPILE_LANGUAGE:C,CXX>:--libc++ --no_wrap_diagnostics -e>
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
add_subdirectory(Src)

# Set the linker options
target_link_options(${PROJECT_NAME} PRIVATE
  --map=${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/$<TARGET_PROPERTY:NAME>.map
  --config=${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/linker/stm32f429xx_flash.icf
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --fpu=vfpv4_sp
  --semihosting
  --vfe
)

# Convert ELF to stripped binaries (.hex)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent
    --strip
    --ihex
    $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf
    $<CONFIG>/$<TARGET_PROPERTY:NAME>.hex
)
