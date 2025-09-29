/*
  Copyright (c) 2020-2025, IAR Systems AB.
  SPDX-License-Identifier: MIT
*/

/*!
  \file    crc32_test.c
  \brief   CRC32 test module
  \version 20250929
*/

#include <errno.h>
#include "acutest.h"
#include "util.h"

void crc32_test()
{
  TEST_CASE("The quick brown fox");
  char * message = "The quick brown fox jumps over the lazy dog";
  int32_t result = crc32(message);
  TEST_CHECK(0x414fa339 == result);
}

TEST_LIST= {
  {"CRC32", crc32_test},

  {NULL, NULL}
};
