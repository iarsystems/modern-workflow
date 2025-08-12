# Generate the stripped binaries (.srec, .hex and .bin)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --srec $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.srec
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --ihex $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.hex
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --bin  $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.bin
)
