#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>

#define TEST_DATA_512BYTE  (128) // 4 * 128 = 512 bytes
#define MAX_TEST           (10)
#define PATTERN_LENGTH     (4)

enum {
  WORDS = 128
};

typedef struct data_s {
  uint32_t word[WORDS];
  size_t length;
} data_t;

const uint8_t* bm_search(const uint8_t *text, const uint8_t *pattern);
uint32_t linear_search(uint32_t x, const data_t *data);
uint16_t crc16(const char * data);
uint32_t crc32(const char * data);
#endif /* __UTIL_H__ */
