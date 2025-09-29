/*
  Copyright (c) 2020-2025, IAR Systems AB.
  SPDX-License-Identifier: MIT
*/

/*!
  \file    crc16_test.c
  \brief   CRC16 test module
  \version 20250929
*/

#include <errno.h>
#include "acutest.h"
#include "util.h"


void crc16_test()
{
  TEST_CASE("The quick brown fox");
  char * message = "The quick brown fox jumps over the lazy dog";
  uint16_t result = crc16(message);
  TEST_CHECK(0x8FDD == result);
}

TEST_LIST= {
  {"CRC16", crc16_test},

  {NULL, NULL}
};
