add_library(CppUTest STATIC)

target_sources(CppUTest PRIVATE
  CommandLineArguments.cpp
  MemoryLeakWarningPlugin.cpp
  TestHarness_c.cpp
  TestRegistry.cpp
  CommandLineTestRunner.cpp
  SimpleString.cpp
  TestMemoryAllocator.cpp
  TestResult.cpp
  JUnitTestOutput.cpp
  TeamCityTestOutput.cpp
  TestFailure.cpp
  TestOutput.cpp
  MemoryLeakDetector.cpp
  TestFilter.cpp
  TestPlugin.cpp
  TestTestingFixture.cpp
  SimpleMutex.cpp
  Utest.cpp
  ../Platforms/Iar/UtestPlatform.cpp
)

target_include_directories(CppUTest PUBLIC
  ${CMAKE_SOURCE_DIR}/CppUTest/include
  ${CMAKE_SOURCE_DIR}/CppUTest/include/CppUTest
)

target_compile_options(CppUTest PRIVATE
  $<$<COMPILE_LANGUAGE:C,CXX>:--libc++ --no_wrap_diagnostics>
  --cpu=cortex-m4
  --fpu=vfpv4_sp
  --libc++
)
