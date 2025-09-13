# Build system for STM32 F070RB Bare Metal Project
#
# Author: J. L. Hay


# Project Parameters

project('STM32 F070RB Bare Metal', 'c')


target = 'target/stm32f070rb'
os = 'SYS_OS'


c_args = [
    '-mcpu=cortex-m0',
    '-mthumb',
    '-Wall',
    '-Werror',
    '--specs=nosys.specs'
]

c_link_args = [
    '-mcpu=cortex-m0',
    '-mthumb',
    '-Wall',
    '--specs=nosys.specs',
    '-nostdlib',
    '-lgcc'
]


# Recursive source file loading

proj_c = []

subdir('sys')
proj_c += sys_c
c_link_args += '-T' + link_script

subdir('src')
proj_c += src_c

inc_dir = include_directories('sys', 'src')


# OS flag

if os == 'SYS_OS'
    c_args += '-DSYS_OS_ENABLED=1'
endif


# Targets

# Executable for debugging
executable('debug', 
    proj_c,
    name_suffix: 'elf',
    c_args: [c_args, '-g'],
    include_directories: inc_dir,
    link_args: c_link_args
)

# Executable for final application
executable('app', 
    proj_c,
    name_suffix: 'elf',
    c_args: [c_args, '-O3'],
    include_directories: inc_dir,
    link_args: c_link_args
)


# TODO:
#  - Executable size
#  - Upload executable
#  - Run debugger
# Difficulties: configuring through cross file