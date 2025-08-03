# "Bare Metal" STM32 Programming
This repository contains the source files for programming an STM32 F070RB
without the use of the STM32 Cube toolchain. This project nominally follows
along with Vivonomicon's tutorial. (See further reading section.)

The current program (main.c) repeatedly increments a value which may be
inspected by GDB. A complete vector table (with most entries pointing to a
default interrupt handler) is loaded as well and should be inspectable with GDB.

## Directories
A map of the directories present in the repository is shown below.
```
stm32-bare-metal/           # Root
├── conf/                   # Configuration files (Meson cross compile conf.)
├── sys/                    # Target system source code and hardware abstraction
├── sim/                    # Simulations
│   └── renode/             # Renode models and configuration
└── src/                    # Application related source code
```

## Build & Debug
The current version of the software is built using meson and may be compiled to
`main.elf` in the build directory of your choosing with the following commands.
```bash
meson setup <build-dir> --cross-file conf/<cross-file>
cd <build-dir>
meson compile
```
The chip can be debugged by running the following commands in separate bash
terminals. I have chosen to use the open source ST Link utility recommended by
Vivonomicon. (See link in further reading section.)
```bash
st-util
arm-none-eabi-gdb <build-dir>/main.elf
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

## Next Steps
Other than following the Vivonomicon tutorial, I'd also like to explore:
 - Simulating the code execution in a framework such as Renode.
 - Building some peripheral drivers from scratch.
 - DIY multithreading.
 - Unit testing.
 - Switch away from meson to a more embedded friendly build chain.

## Further Reading
 - [Vivonomicon "Bare Metal" STM32 article
   series.](https://vivonomicon.com/2018/04/02/bare-metal-stm32-programming-part-1-hello-arm/)
 - [Open source ST Link utilities](https://github.com/stlink-org/stlink)
 - [STM32 F070RB Product
   Page.](https://www.st.com/en/microcontrollers-microprocessors/stm32f070rb.html)
 - [Meson Build System.](https://mesonbuild.com/)
 - [Renode.](https://renode.io/)
