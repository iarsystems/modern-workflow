#include <errno.h>

#include "acutest.h"
#include "util.h"

__root __no_init int          __argc;
__root __no_init const char * __argv;
__root __no_init       char   __argvbuf[1000];

static const uint8_t numbers[]="1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234ABCD56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";
static const uint8_t alphanum[]="123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890ABCDEFGHIJKLMN01234567890";
static const uint8_t pattern0[PATTERN_LENGTH + 1]="ABCD";
static const uint8_t pattern1[]="KLMN";
static const uint8_t pattern2[]="MN01";

void bm_search_test() {
  char res;
  TEST_CASE("numbers - Pattern 0");
  res = *bm_search(numbers, pattern0);
  TEST_CHECK('A' == res);

  TEST_CASE("alphanum - Pattern 1");
  res = *bm_search(alphanum, pattern1);
  TEST_CHECK('K' == res);

  TEST_CASE("alphanum - Pattern 2");
  res = *bm_search(alphanum, pattern2);
  TEST_CHECK('M' == res);
}

TEST_LIST = {
  { "test_bm", bm_search_test },
  { NULL, NULL }
};
