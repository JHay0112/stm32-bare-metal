# "Bare Metal" STM32 Programming
This repository contains the source files for programming an STM32 F070RB
without the use of the STM32 Cube toolchain. This project nominally follows
along with Vivonomicon's tutorial. (See further reading section.)

The current program (core.S) writes the value `0xDEADBEEF` to r7, and repeatedly
increments r0. This can be verified by running the program and using a debugger
such as gdb to inspect the register values.

## Build & Debug
The current version of the software is built by running the following commands
in a bash terminal.
```bash
arm-none-eabi-gcc -x assembler-with-cpp -c -O0 -mcpu=cortex-m0 -mthumb -Wall core.S -o core.o
arm-none-eabi-gcc core.o -mcpu=cortex-m0 -mthumb -Wall --specs=nosys.specs -nostdlib -lgcc -T./stm32f070rb.ld -o main.elf
```
The chip can be debugged by running the following commands in separate bash
terminals. I have chosen to use the open source ST Link utility recommended by
Vivonomicon. (See link in further reading section.)
```bash
st-util
arm-none-eabi-gdb main.elf
```
(As a reminder to myself, `st-util` may be sent to the background with Ctrl-Z
and `bg`. This permits the use of one terminal, though mixes up outputs from gdb
`pgrep st-util` may be used to get its pid to kill it when finished.)

## Next Steps
Other than following the Vivonomicon tutorial, I'd also like to explore:
 - Simulating the code execution in a framework such as Renode.
 - Building some peripheral drivers from scratch.
 - Scheduling?

## Further Reading
 - [Vivonomicon "Bare Metal" STM32 article
   series.](https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/)
 - [Open source ST Link utilities](https://github.com/stlink-org/stlink)
 - [STM32 F070RB Product
   Page.](https://www.st.com/en/microcontrollers-microprocessors/stm32f070rb.html)
 - [Renode](https://renode.io/)
