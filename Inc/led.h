#ifndef __LED_H__
#define __LED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f429ii_aca.h"

void blink(uint8_t * mask);

#ifdef __cplusplus
}
#endif
#endif