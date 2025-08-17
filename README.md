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
4141 when simulating. Currently, the Renode machine does not simulate the
Systick timer.

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
```

## Build & Debug
the current version of this project is being built with the experimental [nobuild](https://github.com/tsoding/nob.h) c build "system", the idea is all you need to build the project is a c complier. to configure the project all you need to do is
```bash
> gcc nob.c -o nob
> ./nob
```

The program output will be within the `build/` folder defined in `nob.c`

## Simulation
A rudimentary Renode simulation is provided in `sim/renode`. To simulate the
software, follow the build instructions and then use the script
`sim/renode/stm32f070rb_init.resc` in the Renode shell. The command to load the
script in the Renode shell follows.
```
include @sim/renode/stm32f070rb_init.resc
```
(Assuming that the Renode shell was started in the project's root directory.)

## Next Steps
Other than following the Vivonomicon tutorial, I'd also like to explore:
 - Simulating the code execution in a framework such as Renode.
 - Building some peripheral drivers from scratch.
 - DIY multithreading.
 - Unit testing.
 - Switch away from meson to a more embedded friendly build chain.

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
