include_guard()

# Set CMake for cross-compiling
set(CMAKE_SYSTEM_NAME Generic)

# Enable all CMake configuration types
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo MinSizeRel)

# Enable IAR C-STAT Static Analysis
option(ENABLE_ICSTAT "Enable IAR C-STAT Static Analysis" OFF)
if(ENABLE_ICSTAT)
  cmake_minimum_required(VERSION 4.1)
  set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
  set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")
endif()

# Facilitate adding C-SPY tests driven by CTest
macro(cspysim TARGET)
  add_test(
    NAME ${TARGET}
    COMMAND /opt/iar/cxarm/common/bin/CSpyBat
            /opt/iar/cxarm/arm/bin/libarmproc.so
            /opt/iar/cxarm/arm/bin/libarmsim2.so
            --plugin=/opt/iar/cxarm/arm/bin/libarmLibsupportUniversal.so
            --debug_file=$<TARGET_FILE:${TARGET}>
            --silent
            --backend
              --cpu=cortex-m4
              --semihosting )
  # SUCCESS is the expected output from acutest
  set_property(TEST ${TARGET} PROPERTY PASS_REGULAR_EXPRESSION SUCCESS)
endmacro()
