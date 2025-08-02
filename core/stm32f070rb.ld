/**
 * STM32F070RB Linker Script.
 * 
 * Author: J. L. Hay
 */


/* End of program stack
   RAM origin + RAM length (16K) */
_estack = 0x20004000; 


/* Minimum left over RAM for stack and dynamic allocation */
_min_leftover_ram = 0x400;

 
/* Memory layout
   B-coded part -> 128K Flash, 16K SRAM */
MEMORY 
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 16K
}


/* Memory divisions */
SECTIONS
{
    /* Flash Sections */

    /* Vector table */
    .vector_table :
    {
        . = ALIGN(4);
        KEEP (*(.vector_table))
        . = ALIGN(4);
    } >FLASH

    /* Program text (code) */
    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        . = ALIGN(4);
    } >FLASH

    /* Read only data (constants) */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } >FLASH


    /* RAM sections */

    /* Data (variables) with initial values */
    _sidata = .;
    .data : AT(_sidata)
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } >RAM

    /* Data without initial values */
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    /* Heap and stack */
    .dynamic_allocations :
    {
        . = ALIGN(4);
        _ssystem_ram = .;
        . = . + _min_leftover_ram;
        . = ALIGN(4);
        _esystem_ram = .;
    } >RAM
}
