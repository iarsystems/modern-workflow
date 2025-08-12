#include <stdint.h>
#include "led.h"

/**
  * @brief  Blink all the LEDs according to the provided mask.
  * @param  uint8_t a mask for the desired effect.
  * @retval None
  */
 void blink(uint8_t * mask)
 {
   uint8_t led_mask = *mask;
   for (LED_e i = LED1; i <= LED8; i++)
   {
     if (led_mask & (1 << i))
     {
       ACA_LED_on(i);
     }
     else
     {
       ACA_LED_off(i);
     }
   }
 }