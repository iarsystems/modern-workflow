// SPDX-License-Identifier: MIT
/**
 * @file crc16_test.c
 * @brief CRC16 unit test.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <errno.h>
#include "acutest.h"
#include "util.h"

void test_crc16_empty() {
  TEST_CASE("CRC16: empty");
  TEST_CHECK(0xFFFF == crc16("", 0));
}

void test_crc16_std_value() {
  TEST_CASE("CRC16: std value");
  TEST_CHECK(0x29B1 == crc16((const uint8_t *)"123456789", 9));
}

void test_crc16_all_zeros() {
  uint8_t data[16] = { 0 };

  TEST_CASE("CRC16: all zeros");
  TEST_CHECK(0x6A0A == crc16(data, 16));
}

void test_crc16_all_ones() {
  uint8_t data[8];
  memset(data, 0xFF, sizeof(data));

  TEST_CASE("CRC16: all ones");
  TEST_CHECK(0x97DF == crc16(data, 8));
}

void test_crc16_fox() {
  uint8_t * message = "The quick brown fox jumps over the lazy dog";

  TEST_CASE("CRC16: The quick brown fox");
  TEST_CHECK(0x8FDD == crc16(message, 43));
}

TEST_LIST= {
  {"test_empty", test_crc16_empty},
  {"test_std_value", test_crc16_std_value},
  {"test_all_zeros", test_crc16_all_zeros},
  {"test_all_ones", test_crc16_all_ones},
  {"test_fox", test_crc16_fox},

  {NULL, NULL}
};
