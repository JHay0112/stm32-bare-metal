
#include "os/systick_interface.h"

#include "target/stm32f070rb/memory_map.h"


void os_target_register_tick_handler(void (*tick_handler)(void))
{

}

void os_target_register_defer_handler(void (*defer_handler)(void))
{

}


void os_set_tick(uint32_t tick_rate)
{
    *ADDR_SYSTICK_RVR = 0x00FFFFFF & tick_rate;
}

void os_enable_tick(void)
{
    // Clear then enable systick
    *ADDR_SYSTICK_CVR = 0b0;
    *ADDR_SYSTICK_CSR |= 0b111;
}