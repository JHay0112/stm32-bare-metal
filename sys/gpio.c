/**
 * GPIO implmentation for STM32F070RB.
 *
 * Author: J. L. Hay
 */


#include "gpio.h"

#include "memory_map.h"


gpio_status gpio_init(gpio_bank_id bank_id)
{
    if (bank_id != GPIOA) {
        return BAD;
    }

    mmap_addr ahbenr = ADDR_RCC + OFFSET_RCC_AHBENR;
    mmap_addr moder = ADDR_GPIOA + OFFSET_GPIO_MODER;
    mmap_addr odr = ADDR_GPIOA + OFFSET_GPIO_ODR;

    // Initialise GPIOA clock
    *ahbenr |= (0b1 << 17);

    // The following code is more appropriate elsewhere
    // (Not to mention that it isn't particularly robust) 

    // Set pin 5 as output
    *moder |= (0b01 << 10);

    // Set pin 5, turn on LED
    *odr |= (0b1 << 5);

    return GOOD;
}