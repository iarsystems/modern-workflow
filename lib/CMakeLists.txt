# Add a library
add_library(util)

# Sources: library
target_sources(util PRIVATE
  bm_search.c
  crc16.c
  crc32.c
  linear_search.c
)

# Properties: library
set_target_properties(
  util
  PROPERTIES
    COMPILE_OPTIONS "--cpu=${CPU};--dlib_config=full;--no_wrap_diagnostics"
)



# Unit tests
add_executable(hello_test)
add_executable(crc16_test)
add_executable(crc32_test)
add_executable(bm_search_test)
add_executable(linear_search_test)

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

# Properties: unit tests
set_target_properties(
  bm_search_test
  crc16_test
  crc32_test
  linear_search_test
  hello_test
  PROPERTIES
    INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/acutest/include  
    COMPILE_OPTIONS "--cpu=${CPU};--dlib_config=full;--no_wrap_diagnostics"
    LINK_OPTIONS "--cpu=${CPU};--semihosting;--redirect=_Printf=_PrintfFullNoMb"
    LINK_LIBRARIES util
)

# Use IAR C-SPY to perform
# unit testing and code coverage
iar_cspysim(hello_test 0)
iar_cspysim(bm_search_test 91)
iar_cspysim(linear_search_test 100)
iar_cspysim(crc16_test 100)
iar_cspysim(crc32_test 100)

