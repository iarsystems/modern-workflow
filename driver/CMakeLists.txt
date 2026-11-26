project(driver)

add_library(driver)

target_compile_definitions(driver
  PRIVATE
    USE_HAL_DRIVER
  PUBLIC
    STM32F429xx
)

target_compile_options(driver PUBLIC
  $<$<COMPILE_LANGUAGE:C,CXX>:--no_wrap_diagnostics>
  $<$<COMPILE_LANGUAGE:ASM>:-s+>
  $<$<COMPILE_LANGUAGE:C>:--dlib_config=full>
  $<$<COMPILE_LANGUAGE:CXX>:--libc++ --no_rtti --no_exceptions>
  --cpu=cortex-m4
  --fpu=vfpv4_sp
)
target_link_options(driver INTERFACE
  --no_wrap_diagnostics
  --config ${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/linker/stm32f429xx_flash.icf
  #--config ${CMAKE_CURRENT_SOURCE_DIR}/cmsis-device-f4/Source/Templates/iar/linker/stm32f429xx_sram.icf
)

add_subdirectory(cmsis_6)
add_subdirectory(cmsis-device-f4)
add_subdirectory(stm32f4xx-hal-driver)

