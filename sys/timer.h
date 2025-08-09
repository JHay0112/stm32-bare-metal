/**
 * Timer configuration interface.
 *
 * Author: J. L. Hay
 */

#ifndef SYS_TIMER_H
#define SYS_TIMER_H


#include <stdint.h>


typedef enum {
    TIMER_SYSTICK
} timer_id;

typedef enum {
    TIMER_GOOD,
    TIMER_BAD,
    TIMER_NOT_IMPL
} timer_status;


timer_status timer_init(timer_id id);
timer_status timer_set(timer_id id, uint32_t val);
timer_status timer_clear(timer_id id);


#endif