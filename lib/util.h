// SPDX-License-Identifier: MIT
/**
 * @file util.h
 * @brief Utility Library header.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <stdbool.h>

#define PATTERN_LENGTH 4
#define RING_BUF_SIZE 256 // Must be power of 2
#define RING_BUF_MASK (RING_BUF_SIZE - 1)
#define WORDS 128

typedef struct data_s {
  uint32_t word[WORDS];
  size_t length;
} data_t;

typedef struct {
    uint8_t buffer[RING_BUF_SIZE];
    uint32_t head; // Write index
    uint32_t tail; // Read index
} ring_buf_t;

const uint8_t* bm_search(const uint8_t *text, const uint8_t *pattern);
uint32_t linear_search(uint32_t x, const data_t *data);
uint16_t crc16(const uint8_t *data, size_t length);
uint32_t crc32(const uint8_t *data, size_t length);

void ring_buf_init(ring_buf_t *rb);
bool ring_buf_is_full(const ring_buf_t *rb);
bool ring_buf_is_empty(const ring_buf_t *rb);
bool ring_buf_push(ring_buf_t *rb, uint8_t byte);
bool ring_buf_pop(ring_buf_t *rb, uint8_t *byte);

#endif /* __UTIL_H__ */
