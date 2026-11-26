include_guard()

enable_language(ASM)
enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable IAR Compiler extensions (-e)
get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
if("C" IN_LIST languages)
  set(CMAKE_C_EXTENSIONS ON)
endif()
if("CXX" IN_LIST languages)
  set(CMAKE_CXX_EXTENSIONS ON)
endif()


# Function: Generate REGEX from a given integer up to 100%
function(regex_range OUTVAR MIN)
  #9[0-9].[0-9][0-9]%
  if (MIN LESS 10)
    set(result "[${MIN}-9].[0-9][0-9]")
  elseif(MIN GREATER 9 AND MIN LESS 100)
    string(SUBSTRING "${MIN}" 0 1 _digit10)
    string(SUBSTRING "${MIN}" 1 1 _digit1)
    math(EXPR _digit10plus1 "${_digit10}+1")
    set(result "(${_digit10}[${_digit1}-9]|[${_digit10plus1}-9][0-9]).[0-9][0-9]")
  elseif(MIN EQUAL 100)
    set(result "100.00")
  else()
    message(FATAL_ERROR "regex_range(): minimal value should be an integer 0<MIN<100.")
  endif()
  set(${OUTVAR} "${result}" PARENT_SCOPE)
endfunction()

# Facilitate adding C-SPY tests driven by CTest
# usage: iar_cspysim(TargetName ExpectedCodeCoverage)
macro(iar_cspysim TARGET CODECOVER)
  find_program(CSPYBAT
    NAMES CSpyBat
          CSpyBat.exe
    PATHS /opt/iar/cxarm
          /opt/iar/ewarmc
          /iar/cxarm-10.10.2
          /iar/ewarmc-10.10.2
    PATH_SUFFIXES common/bin
    NO_DEFAULT_PATH
  REQUIRED
  )
  cmake_path(GET CSPYBAT PARENT_PATH COMMON_DIR)

  find_library(LIBPROC
    NAMES libarmproc.so
          libarmPROC.so
             armproc.dll
    PATHS /opt/iar/cxarm
          /opt/iar/ewarmc
          /iar/cxarm-10.10.2
          /iar/ewarmc-10.10.2
    PATH_SUFFIXES arm/bin
    NO_DEFAULT_PATH
    REQUIRED
  )
  find_library(LIBSIM
    NAMES libarmsim2.so
          libarmSIM2.so
             armsim2.dll
    PATHS /opt/iar/cxarm
          /opt/iar/ewarmc
          /iar/cxarm-10.10.2
          /iar/ewarmc-10.10.2
    PATH_SUFFIXES arm/bin
    NO_DEFAULT_PATH
  )
  find_library(LIBSUPPORT
    NAMES libarmLibsupportUniversal.so
          armLibsupportUniversal.dll
    PATHS /opt/iar/cxarm
          /opt/iar/ewarmc
          /iar/cxarm-10.10.2
          /iar/ewarmc-10.10.2
    PATH_SUFFIXES arm/bin
    NO_DEFAULT_PATH
    REQUIRED
  )

  ### Perform Unit testing using the IAR C-SPY Simulator
  add_test(
    NAME ${TARGET}-cspy-unit-testing
    COMMAND ${CSPYBAT} ${LIBPROC} ${LIBSIM}
      --plugin=${LIBSUPPORT}
      --debug_file=$<TARGET_FILE:${TARGET}>
      --code_coverage_file=$<TARGET_FILE_DIR:${TARGET}>/${TARGET}-code-coverage.log
      --silent
      --backend
        --cpu=cortex-m4
        --fpu=vfpv4_sp
        --semihosting
  )
  # PASS if the output of acutest emits "SUCCESS"
  set_property(TEST ${TARGET}-cspy-unit-testing PROPERTY
    PASS_REGULAR_EXPRESSION "SUCCESS"
  )

  ### Evaluate the IAR C-SPY Code Coverage report
  add_test(
    NAME ${TARGET}-cspy-code-coverage
    COMMAND ${CMAKE_COMMAND} -E cat
      $<TARGET_FILE_DIR:${TARGET}>/${TARGET}-code-coverage.log
  )
  # Get the target name without the "_test" preffix
  string(REGEX REPLACE "test_" "" TARGET_WITHOUT_TEST_PREFFIX ${TARGET})
  # SKIP unit tests for the module "hello_test"
  set_property(TEST ${TARGET}-cspy-code-coverage PROPERTY
    SKIP_REGULAR_EXPRESSION
      "Module \"hello"
  )
  regex_range(CODECOVERPASS ${CODECOVER})
  # PASS if the set-point for the module is >= CODECOVER)
  set_property(TEST ${TARGET}-cspy-code-coverage PROPERTY
    PASS_REGULAR_EXPRESSION
      "Module \"${TARGET_WITHOUT_TEST_PREFFIX}\" coverage: ${CODECOVERPASS}%"
  )
endmacro()

# Use IAR ELF Tool to generate outputs in additional formats
function(iar_elftool tgt)
  add_custom_target(ielftool_hex ALL
    DEPENDS ${tgt}
    COMMAND ${CMAKE_IAR_ELFTOOL}
      --silent
      --strip
      --ihex
      $<TARGET_FILE:${tgt}>
      $<TARGET_FILE_DIR:${tgt}>/${tgt}.hex
  )
endfunction()

# Enable IAR C-STAT Static Analysis for a specific target
macro(enable_iar_cstat_analysis TARGET)
  set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
  set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")
  # Link-time analysis with C-STAT
  get_target_property(target_type ${TARGET} TYPE)
  if(target_type STREQUAL "EXECUTABLE")
    add_custom_command(TARGET ${TARGET} POST_BUILD
      COMMAND ${CMAKE_C_ICSTAT}
        --db=cstat.db
        --checks=cstat_sel_checks.txt
        link_analyze -- ${CMAKE_LINKER} $<TARGET_OBJECTS:${TARGET}>
      COMMAND_EXPAND_LISTS
    )
  endif()
endmacro()

# Make C-STAT alternatively usable from the command line
if(ENABLE_ICSTAT)
  set(CMAKE_C_ICSTAT "${CMAKE_IAR_CSTAT}")
  set(CMAKE_CXX_ICSTAT "${CMAKE_IAR_CSTAT}")
endif()

# Configure C-SPY Debugger launcher in accordance with the environment (VSC vs EW)
if (DEFINED ENV{VSCODE_CMAKE_TOOLS})
  set(IAR_DEBUG_FILE "${PROJECT_SOURCE_DIR}/.vscode/launch.json" CACHE FILEPATH "")

  # Clangd: Generate compiler internal macros
  execute_process(
    COMMAND ${CMAKE_C_COMPILER} . --silent --predef_macros=n "${PROJECT_SOURCE_DIR}/inc/c_macros.h"
    COMMAND ${CMAKE_CXX_COMPILER} . --c++ --libc++ --silent --predef_macros=n "${PROJECT_SOURCE_DIR}/inc/cxx_macros.h"
  )
else()
  if(WIN32)
    set(IAR_DEBUG_FILE "${PROJECT_SOURCE_DIR}/.vscode/launch-ew-win.json" CACHE FILEPATH "")
  else()
    set(IAR_DEBUG_FILE "${PROJECT_SOURCE_DIR}/.vscode/launch-ew-lnx.json" CACHE FILEPATH "")
  endif()
endif()

# Touch `build/DartConfiguration.tcl` (not used)
# for supressing CMake Tools warning about
# missing file during CTest
file(TOUCH ${PROJECT_BINARY_DIR}/DartConfiguration.tcl)

# Touch IAR_CSTAT_CONFIG_FILE for silencing on the IDE, unless specified
# "Failed to import C-STAT settings: no IAR_CSTAT_CONFIG_FILE variable found in cache"
if(NOT DEFINED IAR_CSTAT_CONFIG_FILE)
  file(TOUCH "${PROJECT_BINARY_DIR}/cstat_config.yaml")
  set(IAR_CSTAT_CONFIG_FILE "${PROJECT_BINARY_DIR}/cstat_config.yaml" CACHE FILEPATH "")
endif()


