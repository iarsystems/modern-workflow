enable_testing()

add_library(util)

# Tests
add_executable(bm_search_test)
add_executable(linear_search_test)
add_executable(hello main.c)

# Add Acutest - Unit testing
target_include_directories(util PUBLIC
  ../acutest/include
)

target_sources(util PRIVATE
  bm_search.c
  linear_search.c
)
target_sources(bm_search_test PRIVATE
  bm_search_test.c
)
target_sources(linear_search_test PRIVATE
  linear_search_test.c
)

set_target_properties(
  util
  PROPERTIES
    COMPILE_OPTIONS "--cpu=cortex-m4;--dlib_config=full;-e"
)

set_target_properties(
  bm_search_test
  linear_search_test
  hello
  PROPERTIES
    COMPILE_OPTIONS "--cpu=cortex-m4;--dlib_config=full;-e"
    LINK_LIBRARIES util
    LINK_OPTIONS "--cpu=cortex-m4;--semihosting;--redirect=_Printf=_PrintfFullNoMb"
)

macro(cspybat TARGET)
  add_test(
    NAME ${TARGET}_ctest
    COMMAND /opt/iar/cxarm/common/bin/CSpyBat
            /opt/iar/cxarm/arm/bin/libarmproc.so
            /opt/iar/cxarm/arm/bin/libarmsim2.so
            --plugin=/opt/iar/cxarm/arm/bin/libarmLibsupportUniversal.so
            --debug_file=$<TARGET_FILE:${TARGET}>
            --silent
            --backend
              --cpu=cortex-m4
              --semihosting )
  set_property(TEST ${TARGET}_ctest PROPERTY PASS_REGULAR_EXPRESSION SUCCESS)
endmacro()

cspybat(hello)
cspybat(bm_search_test)
cspybat(linear_search_test)
