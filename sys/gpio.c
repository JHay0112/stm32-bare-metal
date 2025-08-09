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


static const uint32_t AHBENR_BIT_MASK[GPIO_NUM_BANKS] = 
{
    [GPIOA] = (0b1 << 17),
    [GPIOB] = (0b1 << 18)
};


static inline bool gpio_bank_is_supported(gpio_bank_id bank_id)
{
    return (bank_id == GPIOA || bank_id == GPIOB);
}


gpio_status gpio_init(gpio_bank_id bank_id)
{
    if (!gpio_bank_is_supported(bank_id))
    {
        return BAD;
    }

    mmap_addr ahbenr = ADDR_RCC + OFFSET_RCC_AHBENR;

    // Initialise GPIO clock
    *ahbenr |= AHBENR_BIT_MASK[bank_id];

    return GOOD;
}


gpio_status gpio_set(gpio_bank_id bank_id, gpio_pin_id pin_id, gpio_value val)
{
    if (val != 0b0 && val != 0b1)
    {
        return BAD;
    }

    // Get bank information
    mmap_addr bank_addr = BANK_ADDR_MAP[bank_id];
    mmap_addr moder = bank_addr + OFFSET_GPIO_MODER;
    mmap_addr odr = bank_addr + OFFSET_GPIO_ODR;

    // Set pin as output
    *moder |= (0b01 << (2 * pin_id));
    // Set pin value
    *odr = (val << pin_id);

    return GOOD;
}