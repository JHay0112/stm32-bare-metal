/**
 * Main program for STM32 F070RB project.
 * Blindly increments a value forever. Can be inspected with GDB for asserting
 * program works as intended.
 * 
 * Author: J. L. Hay
 */


#include <stdint.h>
#include <stdbool.h>

#include "gpio.h"


int main(void)
{
    uint32_t val = 0;

    gpio_init(GPIOA);

    while (true) {
        val += 1;
    }

    return 0;
}