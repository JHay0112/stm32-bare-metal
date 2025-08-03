# Build system for STM32 F070RB Bare Metal Project
#
# Author: J. L. Hay


# Project Parameters

project('STM32 F070RB Bare Metal', 'c')


c_args = [
    '-mcpu=cortex-m0',
    '-mthumb',
    '-Wall',
    '--specs=nosys.specs',
    '-O0'
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

subdir('src')
proj_c += src_c


# Targets

# Executable for upload or debugging
executable('main', 
    proj_c,
    name_suffix: 'elf',
    c_args: c_args,
    include_directories: include_directories('sys', 'src'),
    link_args: [c_link_args, '-T@0@/@1@'.format(meson.current_source_dir(), link_script[0])]
)


# TODO:
#  - Executable size
#  - Upload executable
#  - Run debugger
# Difficulties: configuring through cross file