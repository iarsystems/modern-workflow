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

# Add source subdirectories
add_subdirectory(CppUTest/src/CppUTest)
add_subdirectory(Drivers)
add_subdirectory(Src)
add_subdirectory(EWARM)

# Set the linker options
target_link_options(${PROJECT_NAME} PRIVATE
  --map ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>/$<TARGET_PROPERTY:NAME>.map
  --no_wrap_diagnostics
  --cpu=cortex-m4
  --fpu=vfpv4_sp
  --semihosting
  --vfe
)

# Link project against CppUTest
target_link_libraries(${PROJECT_NAME} CppUTest)

# Convert ELF to stripped binaries (.srec, .hex and .bin)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --srec $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.srec
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --ihex $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.hex
  COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --bin  $<CONFIG>/$<TARGET_PROPERTY:NAME>.elf $<CONFIG>/$<TARGET_PROPERTY:NAME>.bin
)
