/**
 * Main program for STM32 F070RB project.
 * Blindly increments a value forever. Can be inspected with GDB for asserting
 * program works as intended.
 * 
 * Author: J. L. Hay
 */


#include <stdint.h>
#include <stdbool.h>

#include "metadata.h"

#include "gpio.h"


SYS_METADATA_SET_STR(VERSION, 8, "1.0.0");
SYS_METADATA_SET_STR(AUTHOR, 12, "J. L. Hay");


int main(void)
{
    uint32_t val = 0;

    gpio_init(GPIOA);
    gpio_set(GPIOA, 5, 1);

    while (true) {
        val += 1;
    }

    return 0;
}