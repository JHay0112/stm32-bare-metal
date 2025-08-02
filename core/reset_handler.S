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
.global reset_handler


// Rudimentary reset_handler
.type reset_handler, %function
reset_handler:

    // Reset stack pointer
    LDR  r0, =_estack
    MOV  sp, r0
    MOVS r0, #0


    // Copy data into RAM
    LDR  r1, =_sdata
    LDR  r2, =_edata
    LDR  r3, =_sidata
    B    copy_sidata_loop

    copy_sidata:
        LDR  r4, [r3, r0] // Load from Flash 
        STR  r4, [r1, r0] // Store into RAM
        ADDS r0, r0, #4   // Offset r0

    copy_sidata_loop:
        // Check if all data copied, else copy next word from sidata + data
        ADDS r4, r0, r1
        CMP  r4, r2
        BCC  copy_sidata


    // Fill BSS with zeros
    MOVS r0, #0
    LDR  r1, =_sbss
    LDR  r2, =_ebss
    B    reset_bss_loop

    reset_bss:
        STR  r0, [r1]
        ADDS r1, r1, #4

    reset_bss_loop:
        // Check if all data zeroed out, else continue
        CMP  r1, r2
        B    reset_bss

    
    // Start main method, to be linked at compile time
    B   main

.size reset_handler, .-reset_handler
