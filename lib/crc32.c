// SPDX-License-Identifier: MIT
/**
 * @file crc32.c
 * @brief Simple CRC32 implementation.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define CRC32_POLY 0xEDB88320

static uint32_t crc32_table[256];
static bool table_initialized = false;

static void init_crc32_table(void) {
  if (table_initialized) return;

  for (uint32_t i = 0; i < 256; i++) {
    uint32_t crc = i;
    for (int j = 0; j < 8; j++)
      crc = (crc & 1) ? (crc >> 1) ^ CRC32_POLY : crc >> 1;
    crc32_table[i] = crc;
  }
  table_initialized = true;
}

uint32_t crc32(const uint8_t *data, size_t length) {
  init_crc32_table();

  uint32_t crc = 0xFFFFFFFF;
  for (size_t i = 0; i < length; i++) {
    crc = crc32_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
  }
  return crc ^ 0xFFFFFFFF;
}

