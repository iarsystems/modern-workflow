# CMake 4.4.0+ provides C++20 support for IAR
cmake_minimum_required(VERSION 4.4.0)

# Configure a CMake project
project(modern-workflow)

# Project-wide CMake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(iar-tools)

add_subdirectory(driver)

add_executable(light-effects)
#enable_iar_cstat_analysis(light-effects)

target_include_directories(light-effects PRIVATE inc)

add_subdirectory(src)
add_subdirectory(lib)

target_link_options(light-effects PRIVATE
  --map $<TARGET_FILE_DIR:light-effects>
)

target_link_libraries(light-effects driver)

# Generate additional outputs
iar_elftool(light-effects)
