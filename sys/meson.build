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

link_script = meson.current_source_dir() / target / 'link_script.ld'