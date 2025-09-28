
#include "os/scheduler.h"

#include "target/stm32f070rb/memory_map.h"

#include <stdbool.h>
#include <stdint.h>


static volatile bool g_switch = false;
__attribute__((used)) static volatile uint8_t g_thread = 0;
static void (*g_threads[OS_SCHEDULER_NUM_THREADS])(void);
static volatile uint32_t g_stack[OS_SCHEDULER_NUM_THREADS * OS_SCHEDULER_STACK_SIZE];
__attribute__((used)) static volatile uint32_t g_stack_pointers[OS_SCHEDULER_NUM_THREADS];


void os_tick_handler(void)
{
    __asm volatile ("CPSID i");
    g_switch = true;

    if (g_switch)
    {
        // Setup switch handler
        *ADDR_SCB_ICSR = 1 << 28;
    }
    __asm volatile ("CPSIE i");
}

__attribute__((naked)) void os_context_switch_handler(void)
{
    __asm volatile (".syntax unified");
    __asm volatile (".thumb                      ");
    __asm volatile ("CPSID i                     ");
    __asm volatile ("MRS   r0, psp               "); // Copy PSP
    __asm volatile ("SUBS  r0, #16               ");
    __asm volatile ("STMIA r0!, {r4-r7}          ");
    __asm volatile ("MOV   r4, r8                ");
    __asm volatile ("MOV   r5, r9                ");
    __asm volatile ("MOV   r6, r10               ");
    __asm volatile ("MOV   r7, r11               ");
    __asm volatile ("SUBS  r0, #32               ");
    __asm volatile ("STMIA r0!, {r4-r7}          ");
    __asm volatile ("SUBS  r0, #16               ");
    __asm volatile ("LDR   r1, =g_thread         "); // Load current thread id
    __asm volatile ("LDRB  r2, [r1]              "); // Keep only LSB
    __asm volatile ("LSLS  r2, r2, #2            ");
    __asm volatile ("LDR   r3, =g_stack_pointers "); // Get stack pointer storage area
    __asm volatile ("STR   r0, [r3, r2]          "); // Save SP via offset
    __asm volatile ("LDRB  r2, [r1]              "); // Reload thread id (w/out offset)
    __asm volatile ("ADDS  r2, r2, #1            "); // Next thread (w rollover)
    __asm volatile ("CMP   r2, %0" : : "i" (OS_SCHEDULER_NUM_THREADS));
    __asm volatile ("BNE skip_rollover           ");
    __asm volatile ("MOVS  r2, #0                "); 
    __asm volatile ("skip_rollover:              ");
    __asm volatile ("STRB  r2, [r1]              "); // Update task id
    __asm volatile ("LSLS  r2, r2, #2            ");
    __asm volatile ("LDR   r0, [r3, r2]          "); // Load new SP
    __asm volatile ("LDMIA r0!, {r4-r7}          ");
    __asm volatile ("MOV   r8, r4                ");
    __asm volatile ("MOV   r9, r5                ");
    __asm volatile ("MOV   r10, r6               ");
    __asm volatile ("MOV   r11, r7               ");
    __asm volatile ("LDMIA r0!, {r4-r7}          ");
    __asm volatile ("MSR   psp, r0               ");
    __asm volatile ("LDR   r0, =0xFFFFFFFD       "); // Return to thread mode
    __asm volatile ("CPSIE i                     ");
    __asm volatile ("BX    r0                    ");
}

void os_scheduler_add(void (*handler)(void))
{
    static uint8_t threads_alloced = 0;

    g_threads[threads_alloced] = handler;
    threads_alloced++;
}

void os_scheduler_init(void)
{
    // Set initial stack state for each thread
    for (uint8_t i = 0; i < OS_SCHEDULER_NUM_THREADS; i++)
    {
        const uint32_t stack_top_addr = ((i + 1) * OS_SCHEDULER_STACK_SIZE) - 1;
        uint32_t *sp = (uint32_t *) &g_stack[stack_top_addr];
        g_stack_pointers[i] = *sp;

        *(sp) = 0x01000000; // xPSR, program status
        *(--sp) = (uint32_t) g_threads[i]; // PC
        *(--sp) = 0xFFFFFFFD; // LR, return to PSP

        // Register default values
        --sp;
        for (uint8_t j = 0; j < 12; j--)
        {
            sp[j] = 0;
        }

        g_stack_pointers[i] = (uint32_t) &g_stack[stack_top_addr - 15];
    }
    
    // Startup systick
    uint32_t tick_rate = 8000000 / 100; // Approx 100 times per second
    *ADDR_SYSTICK_RVR = 0x00FFFFFF & tick_rate;
    *ADDR_SYSTICK_CVR = 0b0;
    *ADDR_SYSTICK_CSR |= 0b111;

    // Enable interrupts
    __asm volatile (".syntax unified");
    __asm volatile (".thumb");
    __asm volatile ("MRS r0, psp");
    __asm volatile ("LDR r0, =g_stack");
    __asm volatile ("MOVS r1, %0" : : "i" (OS_SCHEDULER_STACK_SIZE-8));
    __asm volatile ("LSLS r1, r1, #2");
    __asm volatile ("ADD r0, r0, r1");
    __asm volatile ("MSR psp, r0"); // Init PSP
    __asm volatile ("MRS r0, psp");
    __asm volatile ("MRS r2, control");
    __asm volatile ("MOVS r2, #0x03");
    __asm volatile ("MSR control, r2"); // Set control to thread mode
    __asm volatile ("MRS r2, control");
    __asm volatile ("MOVS r3, #0");
    __asm volatile ("MVNS r3, r3");
    __asm volatile ("SUBS r3, #2");
    __asm volatile ("CPSIE i");
    __asm volatile ("ISB");
    __asm volatile ("BX r3");
}