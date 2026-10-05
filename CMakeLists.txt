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

# Setup TOOLKIT_DIR
cmake_path(GET CMAKE_CXX_COMPILER PARENT_PATH BIN_DIR)
cmake_path(GET BIN_DIR PARENT_PATH TOOLKIT_DIR)
# Generate an IAR-compatible compile database
add_custom_target(clangd_compile_commands ALL
  COMMAND ${TOOLKIT_DIR}/../common/bin/iarbuild${CMAKE_HOST_EXECUTABLE_SUFFIX}
    -E clangd_compile_commands
    --output $<TARGET_FILE_DIR:light-effects>/compile_commands.json
    --build_dir ${CMAKE_CURRENT_BINARY_DIR}
    --configuration $<CONFIG>
    --parallel 4
  COMMENT "Generating $<TARGET_FILE_DIR:light-effects>/compile_commands.json"
)
