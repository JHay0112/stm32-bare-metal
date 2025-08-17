/**
 * build program for STM32 F070RB project.
 * builds as intended.
 * 
 * Author: sirlilpanda
 */


#define NOB_IMPLEMENTATION

#include "nob.h"

// the project name
#define PROJECT_NAME \
    "app"

// the complier
#define CC           "arm-none-eabi-gcc"
#define LINK         "-I"

// Some folder paths that we use throughout the build process.
#define BUILD_FOLDER "build/"
#define SRC_FOLDER   "src/"
#define SYS_FOLDER   "sys/"

// all the args needed
#define C_ARGS \
    "-mcpu=cortex-m0", \
    "-mthumb", \
    "-Wall", \
    "-Werror", 


#define LINK_SCRIPT "link_script.ld"

#define C_LINK_ARGS \
    "-mcpu=cortex-m0", \
    "-mthumb", \
    "-Wall", \
    "--specs=nosys.specs", \
    "-nostdlib", \
    "-lgcc", \
    "-T"SYS_FOLDER LINK_SCRIPT

// the files
#define SYS_FILES \
    SYS_FOLDER "reset_handler.S",  \
    SYS_FOLDER "vector_table.S", \
    SYS_FOLDER "clock.c", \
    SYS_FOLDER "timer.c", \
    SYS_FOLDER "gpio.c" \

#define SRC_FILES \
    SRC_FOLDER "main.c"

int main(int argc, char **argv)
{
    // rebuilds nob to update build script (thats right no re-configure when adding files)
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

    Nob_Cmd cmd = {0};

    nob_cmd_append(&cmd, CC);
    nob_cmd_append(&cmd, C_ARGS);
    nob_cc_inputs(&cmd, SYS_FILES, SRC_FILES);
    nob_cc_output(&cmd, BUILD_FOLDER PROJECT_NAME ".elf");
    nob_cmd_append(&cmd, C_LINK_ARGS);

    // nob_cmd_run_sync_and_reset() resets the cmd for you automatically
    if (!nob_cmd_run_sync_and_reset(&cmd)) return 1;

    return 0;
}
