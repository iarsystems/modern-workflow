#include <errno.h>
#include "acutest.h"

int foo(int a) {
  return a + 1;
}

// Test positive numbers
void foo1_test() {
  int result;
  
  TEST_CASE("positive 10");
  result = foo(10);
  TEST_CHECK(11 == result);
  
  TEST_CASE("positive 100");
  result = foo(100);
  TEST_CHECK(101 == result);
  
  TEST_CASE("positive 0xFFFF");
  result = foo(0xFFFF);
  TEST_CHECK(0x10000 == result);
}

// Test negative numbers
void foo2_test() {
  int result;
  
  TEST_CASE("negative 10");
  result = foo(-10);
  TEST_CHECK(-9 == result);
  
  TEST_CASE("negative 100");
  result = foo(-100);
  TEST_CHECK(-99 == result);
  
  TEST_CASE("negative 0xFFFF");
  result = foo(-0xFFFF);
  TEST_CHECK(-0xFFFE == result);
}

// Test overflow
void foo3_test() {
  int result;
  
  TEST_CASE("overflow");
  result = foo(__INT32_T_MAX__);
  TEST_CHECK(__INT32_T_MIN__ == result);
}

TEST_LIST= {
  {"positive", foo1_test},
  {"negative", foo2_test},
  {"overflow", foo3_test},

  {NULL, NULL}
};

