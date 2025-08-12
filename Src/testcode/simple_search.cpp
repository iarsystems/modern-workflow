#include <cstdint>

#include "test_config.h"
#include "CppUTest/TestHarness.h"

const uint8_t numbers[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234AB56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
const uint8_t alphanum[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
const uint8_t pattern0[]="AB";
const uint8_t pattern1[]="ABCDEFGHIJKLMN";
const uint8_t pattern2[]="ABCDEFGHIJKLMN012345";

const uint8_t *simple_search(const uint8_t *text, const uint8_t *pattern)
{
  int32_t i;

  while ((*text) != '\0')
  {
    for (i = 0; pattern[i] != '\0'; i++)
    {
      if (pattern[i] != text[i])
      {
        break;
      }
    }
    if (pattern[i] == '\0')
    {
      return text;
    }
    text++;
  }
  return (NULL);
}

TEST_GROUP(simple_search)
{
  void setup() { (void)pattern2; }
  void teardown() { }
};

TEST(simple_search, testNumbersPattern0)
{
  CHECK_TRUE(simple_search(numbers, pattern0));
}

TEST(simple_search, testAlphanumPattern1)
{
  CHECK_TRUE(simple_search(alphanum, pattern1));
}

TEST(simple_search, testAlphanumPattern2)
{
  CHECK_TRUE(simple_search(alphanum, pattern2));
}