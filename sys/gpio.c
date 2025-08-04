/**
 * GPIO implmentation for STM32F070RB.
 *
 * Author: J. L. Hay
 */


#include <stdbool.h>

#include "gpio.h"

#include "memory_map.h"


static const mmap_addr BANK_ADDR_MAP[GPIO_NUM_BANKS] = 
{
    [GPIOA] = ADDR_GPIOA,
    [GPIOB] = ADDR_GPIOB
};


static inline bool gpio_bank_is_supported(gpio_bank_id bank_id)
{
    return (bank_id == GPIOA);
}


gpio_status gpio_init(gpio_bank_id bank_id)
{
    if (!gpio_bank_is_supported(bank_id))
    {
        return BAD;
    }

    mmap_addr bank_addr = BANK_ADDR_MAP[bank_id];

    mmap_addr ahbenr = ADDR_RCC + OFFSET_RCC_AHBENR;
    mmap_addr moder = bank_addr + OFFSET_GPIO_MODER;
    mmap_addr odr = bank_addr + OFFSET_GPIO_ODR;

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