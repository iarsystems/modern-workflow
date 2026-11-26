// SPDX-License-Identifier: MIT
/**
 * @file crc16.c
 * @brief Simple CRC16 implementation.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <stddef.h>
#include <stdint.h>

#define CRC16_POLY 0x1021

uint16_t crc16(const uint8_t *data, size_t length) {
  uint16_t crc = 0xFFFF;
  
  for (size_t i = 0; i < length; i++) {
    crc ^= (uint16_t)data[i] << 8;
    for (int b = 0; b < 8; b++) {
      crc = (crc & 0x8000) ? (crc << 1) ^ CRC16_POLY : crc << 1;
    }
  }
  return crc;
}
