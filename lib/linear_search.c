#include <stdint.h>
#include <stdlib.h>

#include "util.h"

uint32_t linear_search(uint32_t x, const data_t *data)
{
  volatile uint32_t n = 0;

  while (n < data->length && data->word[n] != x)
  {
    n++;
  }

  if(n < data->length)
  {
    return n;
  }
  return 0xfffffffful;
}

