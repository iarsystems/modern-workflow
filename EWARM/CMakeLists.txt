target_sources(${PROJECT_NAME} PRIVATE
  startup_stm32f429xx.s
)

# Set the linker options
target_link_options(${PROJECT_NAME} PRIVATE
  --config ${CMAKE_CURRENT_SOURCE_DIR}/stm32f429xx_flash.icf
)