/**
 * Hardware interface for scheduler operations. Expects an "ARMish" model of a
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
#ifndef SYS_OS_SCHEDULER_H
#define SYS_OS_SCHEDULER_H


#include <stdint.h>


#define OS_SCHEDULER_NUM_THREADS 2
#define OS_SCHEDULER_STACK_SIZE 256


void os_tick_handler(void);

void os_context_switch_handler(void);


void os_set_tick(uint32_t tick_rate);

void os_enable_tick(void);

void os_scheduler_add (void (*handler)(void));

void os_scheduler_init(void);


#endif
#endif 