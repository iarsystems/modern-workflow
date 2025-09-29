add_library(util)

# Tests
add_executable(hello_test)
add_executable(crc16_test)
add_executable(crc32_test)
add_executable(bm_search_test)
add_executable(linear_search_test)

# Add Acutest - Unit testing
target_include_directories(util PUBLIC
  ../acutest/include
)

# Sources: library
target_sources(util PRIVATE
  bm_search.c
  crc16.c
  crc32.c
  linear_search.c
)
# Sources: unit tests
target_sources(hello_test PRIVATE
  hello_test.c
)
target_sources(crc16_test PRIVATE
  crc16_test.c
)
target_sources(crc32_test PRIVATE
  crc32_test.c
)
target_sources(bm_search_test PRIVATE
  bm_search_test.c
)
target_sources(linear_search_test PRIVATE
  linear_search_test.c
)

# Properties: library
set_target_properties(
  util
  PROPERTIES
    COMPILE_OPTIONS "--cpu=cortex-m4;--dlib_config=full;-e;--no_wrap_diagnostics"
)
# Properties: unit testing
set_target_properties(
  bm_search_test
  crc16_test
  crc32_test
  linear_search_test
  hello_test
  PROPERTIES
    COMPILE_OPTIONS "--cpu=cortex-m4;--dlib_config=full;-e;--no_wrap_diagnostics"
    LINK_LIBRARIES util
    LINK_OPTIONS "--cpu=cortex-m4;--semihosting;--redirect=_Printf=_PrintfFullNoMb"
)

# Register unit tests
iar_cspysim(hello_test)
iar_cspysim(crc16_test)
iar_cspysim(crc32_test)
iar_cspysim(bm_search_test)
iar_cspysim(linear_search_test)
