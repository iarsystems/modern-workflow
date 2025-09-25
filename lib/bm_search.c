#include <stddef.h>
#include <stdint.h>

#include "util.h"

const uint8_t* bm_search(const uint8_t *text, const uint8_t *pattern)
{
  int32_t table[512];
  int32_t text_index, pattern_index, text_len, i;

  for (i = 0; i < 256; i++) {
    table[i] = PATTERN_LENGTH;
  }
  for (i = 0; i < PATTERN_LENGTH - 1; i++) {
    table[pattern[i]] = PATTERN_LENGTH - i - 1;
  }

  for (text_len = 0; text[text_len] != '\0'; ++text_len)
  ;

  text_index = PATTERN_LENGTH - 1;

  while (text_index < text_len) {
    pattern_index = PATTERN_LENGTH - 1;
    while (text[text_index] == pattern[pattern_index]) {
      if (pattern_index == 0) {
        return text + text_index;
      }
      text_index--;
      pattern_index--;
    }

    if (table[text[text_index]] > PATTERN_LENGTH - pattern_index) {
      text_index += table[text[text_index]];
    } else {
      text_index += PATTERN_LENGTH - pattern_index;
    }
  }

  return NULL;
}

