include_guard()

# Set CMake for cross-compiling
set(CMAKE_SYSTEM_NAME Generic)

# Enable MinSizeRel
set(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo MinSizeRel)

# Enable IAR C-STAT Static Analysis
option(ENABLE_ICSTAT "Enable IAR C-STAT Static Analysis" OFF)
if(ENABLE_ICSTAT)
  cmake_minimum_required(VERSION 4.1)
  set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
  set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")
endif()

# Facilitate adding C-SPY tests driven by CTest
macro(iar_cspysim TARGET)
  find_program(CSPYBAT
    NAMES CSpyBat CSpyBat.exe
    HINTS /opt/iar/cxarm /opt/iarsystems/bxarm
    PATH_SUFFIXES common/bin
    REQUIRED
  )
  cmake_path(GET CSPYBAT PARENT_PATH COMMON_DIR)

  find_library(LIBPROC
    NAMES libarmproc.so libarmPROC.so
    HINTS /opt/iar/cxarm /opt/iarsystems/bxarm
    PATH_SUFFIXES arm/bin
    REQUIRED
  )
  find_library(LIBSIM
    NAMES libarmsim2.so libarmSIM2.so
    HINTS /opt/iar/cxarm /opt/iarsystems/bxarm
    PATH_SUFFIXES arm/bin
    REQUIRED
  )
  find_library(LIBSUPPORT
    NAMES libarmLibsupportUniversal.so
    HINTS /opt/iar/cxarm /opt/iarsystems/bxarm
    PATH_SUFFIXES arm/bin
    REQUIRED
  )

  add_test(
    NAME ${TARGET}
    COMMAND ${CSPYBAT} ${LIBPROC} ${LIBSIM}
      --plugin=${LIBSUPPORT}
      --debug_file=$<TARGET_FILE:${TARGET}>
      --silent
      --backend
        --cpu=cortex-m4
        --semihosting )
  # SUCCESS is the expected output from acutest
  set_property(TEST ${TARGET} PROPERTY PASS_REGULAR_EXPRESSION SUCCESS)
endmacro()

# Generate additional outputs
function(iar_elftool tgt)
  add_custom_command(TARGET ${tgt} POST_BUILD
    COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --ihex $<TARGET_FILE:${tgt}> $<CONFIG>/$<TARGET_PROPERTY:${tgt},NAME>.hex
    COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --srec $<TARGET_FILE:${tgt}> $<CONFIG>/$<TARGET_PROPERTY:${tgt},NAME>.srec
    COMMAND ${CMAKE_IAR_ELFTOOL} --silent --strip --bin $<TARGET_FILE:${tgt}> $<CONFIG>/$<TARGET_PROPERTY:${tgt},NAME>.bin
)
endfunction()

# Touch the cachedVariables from CMakePresets
set(TOOLKIT_DIR ${TOOLKIT_DIR})
set(SELECTED_TOOL ${SELECTED_TOOL})

