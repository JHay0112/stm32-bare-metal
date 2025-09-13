# Build instructions for system components
#
# Author: J. L. Hay


sys_c = files(
    target / 'reset_handler.S', 
    target / 'vector_table.S',
    target / 'clock.c',
    target / 'timer.c',
    target / 'gpio.c'
)

if os == 'OS_SYS'
    sys_c += files(
        target / 'systick_interface.c'
    )
endif

link_script = meson.current_source_dir() / target / 'link_script.ld'