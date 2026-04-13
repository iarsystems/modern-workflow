include_guard()

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
  # Get the target name without the "_test" suffix
  string(REGEX REPLACE "_test" "" TARGET_WITHOUT_TEST_SUFFIX ${TARGET})
  # SKIP unit tests for the module "hello_test"
  set_property(TEST ${TARGET}-cspy-code-coverage PROPERTY
    SKIP_REGULAR_EXPRESSION
      "Module \"hello"
  )
  regex_range(CODECOVERPASS ${CODECOVER})
  # PASS if the set-point for the module is >= CODECOVER)
  set_property(TEST ${TARGET}-cspy-code-coverage PROPERTY
    PASS_REGULAR_EXPRESSION
      "Module \"${TARGET_WITHOUT_TEST_SUFFIX}\" coverage: ${CODECOVERPASS}%"
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

# Configure launcher
set(IAR_DEBUG_FILE "${PROJECT_SOURCE_DIR}/.vscode/launch.json" CACHE FILEPATH "")

# Touch `build/DartConfiguration.tcl` (not used)
# for supressing CMake Tools warning about
# missing file during CTest
file(TOUCH ${CMAKE_BINARY_DIR}/DartConfiguration.tcl)
