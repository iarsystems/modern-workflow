// SPDX-License-Identifier: MIT
/**
 * @file ring_buffer.c
 * @brief Simple ring buffer implementation.
 *
 * @copyright Copyright (c) 2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "util.h"

void ring_buf_init(ring_buf_t *rb) {
  rb->head = 0;
  rb->tail = 0;
}

bool ring_buf_is_full(const ring_buf_t *rb) {
  return ((rb->head - rb->tail) == RING_BUF_SIZE);
}

bool ring_buf_is_empty(const ring_buf_t *rb) {
  return (rb->head == rb->tail);
}

bool ring_buf_push(ring_buf_t *rb, uint8_t byte) {
  if (ring_buf_is_full(rb)) return false;
  rb->buffer[rb->head & RING_BUF_MASK] = byte;
  rb->head++;
  return true;
}

bool ring_buf_pop(ring_buf_t *rb, uint8_t *byte) {
  if (ring_buf_is_empty(rb)) return false;
  *byte = rb->buffer[rb->tail & RING_BUF_MASK];
  rb->tail++;
  return true;
}
