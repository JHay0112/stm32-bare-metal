/**
 * Main program for STM32 F070RB project.
 * Blindly increments a value forever. Can be inspected with GDB for asserting
 * program works as intended.
 * 
 * Author: J. L. Hay
 */


#include <stdint.h>
#include <stdbool.h>

#include "hal/metadata.h"

#include "hal/gpio.h"

#include "os/scheduler.h"


SYS_METADATA_SET_STR(VERSION, 8, "1.0.0");
SYS_METADATA_SET_STR(AUTHOR, 12, "J. L. Hay");


static volatile uint32_t counter_val = 0;
static volatile gpio_value led_val = 0;


void gpio_thread(void)
{
    while (1)
    {
        gpio_set(GPIOA, 5, led_val);

        if (led_val == 0)
        {
            led_val = 1;
        }
        else 
        {
            led_val = 0;
        }
    }
}

void math_thread(void)
{
    while (1)
    {
        counter_val += 1;
    }
}


int main(void)
{
    os_scheduler_add(gpio_thread);
    os_scheduler_add(math_thread);
    os_scheduler_init();
}