add_subdirectory(acutest)

# Add a utility library example
add_library(util)
target_sources(util PRIVATE
  bm_search.c
  crc16.c
  crc32.c
  linear_search.c
  ring_buffer.c
)
target_link_libraries(util PUBLIC driver)

# Examples of unit tests for the utility library
add_executable(test_bm_search)
target_sources(test_bm_search PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    bm_search_test.c
)
target_link_libraries(test_bm_search PRIVATE util acutest)
set_property(FILE_SET skip_lint TARGET test_bm_search PROPERTY SKIP_LINTING ON)
iar_cspysim(test_bm_search 91)

add_executable(test_crc16)
target_sources(test_crc16 PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    crc16_test.c
)
target_link_libraries(test_crc16 PRIVATE util acutest)
set_property(FILE_SET skip_lint TARGET test_crc16 PROPERTY SKIP_LINTING ON)
iar_cspysim(test_crc16 100)

add_executable(test_crc32)
target_sources(test_crc32 PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    crc32_test.c
)
target_link_libraries(test_crc32 util acutest)
set_property(FILE_SET skip_lint TARGET test_crc32 PROPERTY SKIP_LINTING ON)
iar_cspysim(test_crc32 100)

add_executable(test_hello)
target_sources(test_hello PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    hello_test.c
)
target_link_libraries(test_hello PRIVATE util acutest)
set_property(FILE_SET skip_lint TARGET test_hello PROPERTY SKIP_LINTING ON)
iar_cspysim(test_hello 0)

add_executable(test_linear_search)
target_sources(test_linear_search PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    linear_search_test.c
)
target_link_libraries(test_linear_search PRIVATE util acutest)
set_property(FILE_SET skip_lint TARGET test_linear_search PROPERTY SKIP_LINTING ON)
iar_cspysim(test_linear_search 100)

add_executable(test_ring_buffer)
target_sources(test_ring_buffer PRIVATE FILE_SET skip_lint TYPE SOURCES
  FILES
    ring_buffer_test.c
)
target_link_libraries(test_ring_buffer PRIVATE util acutest)
set_property(FILE_SET skip_lint TARGET test_ring_buffer PROPERTY SKIP_LINTING ON)
iar_cspysim(test_ring_buffer 86)
