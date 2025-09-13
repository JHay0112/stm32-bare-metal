/**
 * Timer configuration interface implementation for STM32F070RB.
 *
 * Author: J. L. Hay
 */


#include <stdbool.h>

#include "hal/timer.h"

#include "target/stm32f070rb/memory_map.h"


static inline bool timer_is_supported(timer_id id)
{
    return (id == TIMER_SYSTICK);
}


timer_status timer_init(timer_id id)
{
    if (!timer_is_supported(id))
    {
        return TIMER_BAD;
    }

    // Systick timer initialisation
    // Systick should have its value set before initialisation!
    timer_clear(id);
    *ADDR_SYSTICK_CSR |= 0b111; // Start

    return TIMER_GOOD;
}


timer_status timer_set(timer_id id, uint32_t val)
{
    if (!timer_is_supported(id))
    {
        return TIMER_BAD;
    }

    // Write value to systick reg (24 bit mask)
    *ADDR_SYSTICK_RVR = 0x00FFFFFF & val;

    return TIMER_GOOD;
}


timer_status timer_clear(timer_id id)
{
    if (!timer_is_supported(id))
    {
        return TIMER_BAD;
    }

    // Clear systick reg
    *ADDR_SYSTICK_CVR = 0b0; // Clear current value

    return TIMER_GOOD;
}