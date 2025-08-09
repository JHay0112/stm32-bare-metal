/**
 * System clock configuration interface implementation for STM32F070RB.
 *
 * Author: J. L. Hay
 */


#include "clock.h"


// Default internal oscillator: 8 MHz.
// May be configured to use external clock sources or divide down.
static const uint32_t CLOCK_HSI_FREQ = 8000000; 


uint32_t clock_get_freq(void)
{
    return CLOCK_HSI_FREQ;
}