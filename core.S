/**
 * Initialision for STM32F070RB vector table and main program.
 *
 * Author: J. L. Hay
 */ 


// Syntax options and target info
.syntax unified
.thumb
.cpu cortex-m0
.fpu softvfp


// Global memory locations
// Marked global to ensure availability
.global vtable
.global reset_handler


// Vector table
.type vtable, %object
vtable:
    .word _estack
    .word reset_handler
.size vtable, .-vtable


// Rudimentary reset_handler
.type reset_handler, %function
reset_handler:

    // Reset stack pointer
    LDR  r0, =_estack
    MOV  sp, r0

    // Set register values in endless loop
    LDR  r7, =0xDEADBEEF
    MOVS r0, #0
    main_loop:
        ADDS r0, r0, #1
        B    main_loop

.size reset_handler, .-reset_handler
