// SPDX-License-Identifier: MIT
/**
 * @file crc32_test.c
 * @brief CRC32 unit test.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <errno.h>
#include "acutest.h"
#include "util.h"

void test_crc32_empty() {
  TEST_CASE("CRC32: empty");
  TEST_CHECK(0x00000000 == crc32("", 0));
}

void test_crc32_single_char() {
  TEST_CASE("CRC32: single char");
  TEST_CHECK(0xE8B7BE43 == crc32((const uint8_t *)"a", 1));
}

void test_crc32_short_strings() {
  TEST_CASE("CRC32: short strings");
  TEST_CHECK(0x352441C2 == crc32((const uint8_t *)"abc", 3));
  TEST_CHECK(0xF7D18982 == crc32((const uint8_t *)"Hello", 5));
}

void test_crc32_std_value() {
  TEST_CASE("CRC32: std value");
  TEST_CHECK(0xCBF43926 == crc32((const uint8_t *)"123456789", 9));
}

void test_crc32_all_zeros() {
  uint8_t data[32] = { 0 };

  TEST_CASE("CRC32: all zeros");
  TEST_CHECK(0x190A55AD == crc32(data, 32));
}

void test_crc32_all_ones() {
  uint8_t data[32];
  memset(data, 0xFF, sizeof(data));

  TEST_CASE("CRC32: all ones");
  TEST_CHECK(0xFF6CAB0B == crc32(data, 32));
}

void test_crc32_binary_ascending() {
  uint8_t data[32];
  for (uint32_t i = 0; i < 32; i++) {
    data[i] = (uint8_t)i;
  }

  TEST_CASE("CRC32: binary ascending");
  TEST_CHECK(0x91267E8A == crc32(data, 32));
}

void test_crc32_fox() {
  uint8_t * message = "The quick brown fox jumps over the lazy dog";

  TEST_CASE("CRC32: The quick brown fox");
  TEST_CHECK(0x414fa339 == crc32(message, 43));
}

TEST_LIST= {
  {"test_empty", test_crc32_empty},
  {"test_single_char", test_crc32_single_char},
  {"test_short_strings", test_crc32_short_strings},
  {"test_std_value", test_crc32_std_value},
  {"test_all_zeros", test_crc32_all_zeros},
  {"test_all_ones", test_crc32_all_ones},
  {"test_binary_ascending", test_crc32_binary_ascending},
  {"test_fox", test_crc32_fox},

  {NULL, NULL}
};
