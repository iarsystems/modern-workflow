// SPDX-License-Identifier: MIT
/**
 * @file ring_buffer_test.c
 * @brief Ring Buffer unit test.
 *
 * @copyright Copyright (c) 2020-2026 IAR Systems AB.
 *            All rights reserved.
 */

#include <stdint.h>
#include <errno.h>

#include "acutest.h"
#include "util.h"

void ring_buffer_init_test() {
  ring_buf_t rb;

  ring_buf_init(&rb);
  TEST_CASE("Ring Buffer - Initialization");
  TEST_CHECK(ring_buf_is_empty(&rb));
  TEST_CHECK(!ring_buf_is_full(&rb));
  TEST_CHECK(!ring_buf_is_full(&rb));
}

void ring_buffer_pp_test() {
  ring_buf_t rb;
  uint8_t val;

  ring_buf_init(&rb);
  TEST_CASE("Ring Buffer - Push & Pop");
  TEST_CHECK(ring_buf_push(&rb, 10));
  TEST_CHECK(!ring_buf_is_empty(&rb));
  TEST_CHECK(ring_buf_pop(&rb, &val));
  TEST_CHECK(10 == val);
  TEST_CHECK(ring_buf_is_empty(&rb));
}

void ring_buffer_wa_test() {
  ring_buf_t rb;
  uint8_t val;

  ring_buf_init(&rb);
  TEST_CASE("Ring Buffer - Wrap-around");
  for (uint32_t i = 0; i < RING_BUF_SIZE; i++) {
    TEST_CHECK(ring_buf_push(&rb, (uint8_t)i));
  }
  TEST_CHECK(ring_buf_is_full(&rb));
  TEST_CHECK(false == ring_buf_push(&rb, 90));
  for (uint32_t i = 0; i < RING_BUF_SIZE; i++) {
    TEST_CHECK(ring_buf_pop(&rb, &val));
    TEST_CHECK(val == (uint8_t)i);
  }
}

TEST_LIST = {
  { "test_ring_buffer_init", ring_buffer_init_test },
  { "test_ring_buffer_pp", ring_buffer_pp_test },
  { "test_ring_buffer_wa", ring_buffer_wa_test },

  { NULL, NULL }
};
