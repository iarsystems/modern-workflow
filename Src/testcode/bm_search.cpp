#include <cstddef>
#include <cstdint>

#include "test_config.h"
#include "CppUTest/TestHarness.h"

#define PATTERN_LENGTH     (4)

static const uint8_t numbers[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234ABCD56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
static const uint8_t alphanum[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const uint8_t pattern0[PATTERN_LENGTH + 1]="ABCD";
static const uint8_t pattern1[]="KLMN";
static const uint8_t pattern2[]="MN01";

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

TEST_GROUP(bm_search)
{
  void setup() { }
  void teardown() { }
};

TEST(bm_search, testNumbersPattern0)
{
  CHECK_EQUAL('A', *bm_search(numbers, pattern0));
}

TEST(bm_search, testAlphanumPattern1)
{
  CHECK_EQUAL('K', *bm_search(alphanum, pattern1));
}

TEST(bm_search, testAlphanumPattern2)
{
  CHECK_EQUAL('M', *bm_search(alphanum, pattern2));
}