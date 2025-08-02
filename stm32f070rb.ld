/**
 * STM32F070RB Linker Script.
 * 
 * Author: J. L. Hay
 */

 
/* Memory layout
   B-coded part -> 128K Flash, 16K SRAM */
MEMORY 
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 16K
}

/* End of program stack
   RAM origin + RAM length (16K) */
_estack = 0x20004000; 
