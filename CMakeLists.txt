# This CMake project uses CMake v3.20 or later
cmake_minimum_required(VERSION 3.20)

# Set CMake for cross-compiling
set(CMAKE_SYSTEM_NAME Generic)

# Enable all CMake configuration types
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo MinSizeRel)

# Include `./cmake` to the CMake's module path
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Declare a CMake project
project(light-effects LANGUAGES CXX C ASM)

# Add the executable target
add_executable(${PROJECT_NAME})

# Set the target's compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<COMPILE_LANGUAGE:C,CXX>:--libc++ --no_wrap_diagnostics>
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

# Convert ELF to usual binary outputs
include(ielftool)