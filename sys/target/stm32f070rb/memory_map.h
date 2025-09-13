/**
 * STM32F070RB Memory Map.
 * This is not intended for direct use in application code. (i.e. src.)
 *
 * Author: J. L. Hay
 */

#ifndef SYS_MEMORY_MAP_H
#define SYS_MEMORY_MAP_H


#include <stdint.h>


typedef uint32_t *mmap_addr;
typedef uint32_t  mmap_offset;


// Systick: Cortex-M internal clock
static const mmap_addr ADDR_SYSTICK_CSR = (mmap_addr) 0xE000E010;
static const mmap_addr ADDR_SYSTICK_RVR = (mmap_addr) 0xE000E014;
static const mmap_addr ADDR_SYSTICK_CVR = (mmap_addr) 0xE000E018;
static const mmap_addr ADDR_SYSTICK_CALIB = (mmap_addr) 0xE000E01C;


// RCC: Reset and Clock Control
static const mmap_addr ADDR_RCC = (mmap_addr) 0x40021000;
static const mmap_offset OFFSET_RCC_AHBENR = (mmap_offset) 5;


// GPIO: General Purpose Input and Output
static const mmap_addr ADDR_GPIOA = (mmap_addr) 0x48000000;
static const mmap_addr ADDR_GPIOB = (mmap_addr) 0x48000400;

static const mmap_offset OFFSET_GPIO_MODER = (mmap_offset) 0;
static const mmap_offset OFFSET_GPIO_OTYPER = (mmap_offset) 1;
static const mmap_offset OFFSET_GPIO_ODR = (mmap_offset) 5;


#endif 