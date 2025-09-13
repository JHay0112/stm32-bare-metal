/**
 * Hardware interface for system tick operations. Expects an "ARMish" model of a
 * highest priority periodic tick for OS operations, and a lowest priority
 * handler for deferring tasks e.g. context switching.
 *
 * See the Cortex-M exception model for more information about the model this is
 * developed with inspiration from:
 * https://developer.arm.com/documentation/107706/0100/System-exceptions
 *
 * Author: J. L. Hay
 */

#if SYS_OS_ENABLED
#ifndef SYS_OS_SYSTICK_INTERFACE_H
#define SYS_OS_SYSTICK_INTERFACE_H


#include <stdint.h>


void os_target_register_tick_handler(void (*tick_handler)(void));

void os_target_register_defer_handler(void (*defer_handler)(void));


void os_set_tick(uint32_t tick_rate);

void os_enable_tick(void);


#endif
#endif 