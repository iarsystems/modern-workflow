/*
  Copyright (c) 2020-2025, IAR Systems AB.
  SPDX-License-Identifier: MIT
*/

/*!
  \file    crc32.c
  \brief   Software implementation for CRC32
  \version 20250929
*/

#include <stddef.h>
#include <stdint.h>

#define CRC32_POLY 0xEDB88320

uint32_t crc32(const char* data)
{
  uint32_t crc = 0xFFFFFFFF;
  while (*data)
  {
    crc ^= (uint8_t)(*data++);
    for (int i = 0; i < 8; i++)
    {
      if (crc & 1)
        crc = (crc >> 1) ^ CRC32_POLY;
      else
        crc >>= 1;
    }
  }
  return ~crc;
}
