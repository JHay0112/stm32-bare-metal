/**
 * Timer configuration interface implementation for STM32F070RB.
 *
 * Author: J. L. Hay
 */


#include <stdbool.h>

#include "hal/timer.h"


timer_status timer_init(timer_id id)
{
    return TIMER_BAD;
}


timer_status timer_set(timer_id id, uint32_t val)
{
    return TIMER_BAD;
}


timer_status timer_clear(timer_id id)
{
    return TIMER_BAD;
}