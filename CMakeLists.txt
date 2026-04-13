cmake_minimum_required(VERSION 3.31)

# Configure a CMake project
project(modern-workflow)
enable_language(ASM)

# Target CPU
set(CPU Cortex-M4)

# Enable CTest support
enable_testing()

# Enable IAR C-STAT Static Analysis
option(ENABLE_ICSTAT "Enable IAR C-STAT Static Analysis" OFF)
if(ENABLE_ICSTAT)
  set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
  set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")
endif()

# Enable IAR Compiler Extensions\
set(CMAKE_C_EXTENSIONS ON)

# Project-specific CMake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(iar-tools)

# Add library's sources
add_subdirectory(lib)

# Add application's sources
add_subdirectory(src)
