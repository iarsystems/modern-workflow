/*
  Copyright (c) 2020-2025, IAR Systems AB.
  SPDX-License-Identifier: MIT
*/

/*!
  \file    crc16.c
  \brief   Software implementation for CRC16
  \version 20250929
*/

#include <stddef.h>
#include <stdint.h>

#define CRC16_POLY 0x1021

uint16_t crc16(const char * data)
{
  uint16_t crc = 0xFFFF; 

  while (*data)
  {
    crc ^= ((uint8_t)(*data++) << 8); 
    for (int i = 0; i < 8; i++)
    {
      if (crc & 0x8000)
        crc = (crc << 1) ^ CRC16_POLY;
      else
        crc <<= 1;
    }
  }
  return crc;
}
