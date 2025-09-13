# "Bare Metal" STM32 Programming
This repository contains the source files for programming an STM32 F070RB
without the use of the STM32 Cube toolchain. This project nominally follows
along with Vivonomicon's tutorial. (See further reading section.)

The current program (main.c) repeatedly increments a value which may be
inspected by GDB. It also flashes GPIO PA5 which is associated with the user LED
on the NUCLEO board for the STM32 F070RB using the SysTick timer (built in to
the Cortex-M CPU). A complete vector table (with most entries pointing to a
default interrupt handler) is loaded as well and should be inspectable with GDB
or nm.

A Renode machine description is provided in `sim/renode` that can be used to
simulate the code and peripherals. A GDB server is automatically started on port
4141 when simulating.

## Directories
A map of the directories present in the repository is shown below.
```
stm32-bare-metal/           # Root
├── conf/                   # Configuration files (Meson cross compile conf.)
├── docs/                   # Additional notes and information
├── sim/                    # Simulations
│   └── renode/             # Renode models and configuration
├── src/                    # Application related source code
└── sys/                    # Target system source code and hardware abstraction
    ├── hal/                # Headers for hardware abstraction
    └── target/             # Target system source code, includes HAL code
```

## Build & Debug
The current version of the software is built using meson and may be compiled to
`debug.elf` in the build directory of your choosing with the following commands.
```bash
meson setup <build-dir> --cross-file conf/<cross-file>
cd <build-dir>
meson compile
```
On an x86 Linux host with a gcc toolchain (the only supported host at the time
of writing) and `build` as the selected directory, these commands become the
following.
```bash
meson setup build --cross-file conf/cross_linux_x86.ini
cd build
meson compile
```

The chip can be debugged by running the following commands in separate bash
terminals. I have chosen to use the open source ST Link utility recommended by
Vivonomicon. (See link in further reading section.)
```bash
st-util
arm-none-eabi-gdb <build-dir>/debug.elf
```
(As a reminder to myself, `st-util` may be sent to the background with Ctrl-Z
and `bg`. This permits the use of one terminal, though mixes up outputs from GDB
`pgrep st-util` may be used to get its pid to kill it when finished.)

## Simulation
A rudimentary Renode simulation is provided in `sim/renode`. To simulate the
software, follow the build instructions and then use the script
`sim/renode/stm32f070rb_init.resc` in the Renode shell. The command to load the
script in the Renode shell follows.
```
include @sim/renode/stm32f070rb_init.resc
```
(Assuming that the Renode shell was started in the project's root directory.)

## Branches
At the time of writing, there is a branch of the repository `exp/nob` that
demonstrates the ["nob" build system](https://github.com/tsoding/nob.h) as an
alternative to Meson. The objective of nob is to provide a build system for C
projects that requires only the C compiler as a dependency. This branch was
provided by [@sirlilpanda](https://github.com/sirlilpanda)
([website](https://sirlilpanda.studio/)).  

## Next Steps
Other than following the Vivonomicon tutorial, I'd also like to explore:
 - Simulating the code execution in a framework such as Renode.
 - Building some peripheral drivers from scratch.
 - Unifying the hardware description for peripheral drivers and simulation by
   using device trees.
 - DIY multithreading.
 - Unit testing.
 - Switch away from meson to a more embedded friendly build chain. See `exp/nob`
   for nob-based alternative. (More information in the branches section.)

## Further Documentation
 - [VSCodium Configuration](./docs/vscodium.md)

## Further Resources
 - [Vivonomicon "Bare Metal" STM32 article
   series.](https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/)
 - [Open source ST Link utilities](https://github.com/stlink-org/stlink)
 - [STM32 F070RB Product
   Page.](https://www.st.com/en/microcontrollers-microprocessors/stm32f070rb.html)
 - [Meson Build System.](https://mesonbuild.com/)
 - [Renode.](https://renode.io/)
