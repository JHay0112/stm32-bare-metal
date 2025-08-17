/**
 * Main program for STM32 F070RB project.
 * Blindly increments a value forever. Can be inspected with GDB for asserting
 * program works as intended.
 * 
 * Author: J. L. Hay
 */


#include <stdint.h>
#include <stdbool.h>

// it would be really nice if this existed
// #include "metadata.h"

#include "../sys/clock.h"
#include "../sys/timer.h"
#include "../sys/gpio.h"


// SYS_METADATA_SET_STR(VERSION, 8, "1.0.0");
// SYS_METADATA_SET_STR(AUTHOR, 12, "J. L. Hay");


static volatile gpio_value led_val = 0;


void systick_handler(void)
{
    if (led_val == 0)
    {
        led_val = 1;
    }
    else 
    {
        led_val = 0;
    }

    gpio_set(GPIOA, 5, led_val);

    timer_clear(TIMER_SYSTICK);
}


int main(void)
{
    uint32_t val = 0;

    gpio_init(GPIOA);
    gpio_set(GPIOA, 5, 1);

    uint32_t systick_period = clock_get_freq() / 10;
    timer_set(TIMER_SYSTICK, systick_period);
    timer_init(TIMER_SYSTICK);

    while (true) {
        val += 1;
    }

    return 0;
}