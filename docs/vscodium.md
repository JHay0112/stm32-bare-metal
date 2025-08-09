# VSCodium Integration
This document includes additional instructions for building and debugging with
VSCodium and Renode. 

## Extensions
I use the following extensions:
 1. [clangd](https://github.com/clangd/vscode-clangd.git): For syntax
    highlighting.
 2. [Meson](https://github.com/mesonbuild/vscode-meson.git): For building.
 3. [Cortex Debug](https://github.com/Marus/cortex-debug.git): For debugging.

## Configuration
The Cortex Debug extension requires additional configuration for use with
physical and simulated hardware. The following settings should be included in
`.vscode/launch.json`.
```json
{
    "version": "0.2.0",
    "configurations": [

        {
            "name": "Physical Debug",
            "cwd": "${workspaceFolder}",
            "executable": "./build/main.elf",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "stutil"
        },

        {
            "name": "Renode Debug",
            "cwd": "${workspaceRoot}",
            "executable": "${workspaceRoot}/build/main.elf",
            "device": "STM32F070RB",
            "request": "launch",
            "type": "cortex-debug",
            "runToEntryPoint": "main",
            "servertype": "external",
            "gdbTarget": "localhost:4141",
            "toolchainPrefix": "arm-none-eabi-",
            "gdbPath": "arm-none-eabi-gdb"
        }
    ]
}
```

Once configured, both runners should be available in the "Run and Debug" menu.

To debug with Renode it is necessary to manually initialise the Renode machine.
This is achieved by running the following command in the Renode shell.
```
include @sim/renode/stm32f070rb_init.resc
```