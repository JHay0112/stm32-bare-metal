/**
 * Vector table definition.
 * 
 * Adapted from:
 * https://github.com/STMicroelectronics/cmsis-device-f0/blob/master/Source/Templates/gcc/startup_stm32f070xb.s
 *
 * Author: J. L. Hay
 */


// Syntax options and target info
.syntax unified
.thumb
.cpu cortex-m0
.fpu softvfp


// Global memory locations
// Marked global to ensure availability
.global vtable
.global default_interrupt_handler


// Vector table
.type vtable, %object
.section .vector_table,"a",%progbits
vtable:
    .word _estack
    .word reset_handler
    .word nmi_handler
    .word hard_fault_handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word svc_handler
    .word 0
    .word 0
    .word os_context_switch_handler
    .word os_tick_handler
    .word wwdg_irq_handler
    .word 0                                 
    .word rtc_irq_handler
    .word flash_irq_handler
    .word rcc_irq_handler
    .word exti0_1_irq_handler
    .word exti2_3_irq_handler
    .word exti4_15_irq_handler
    .word 0
    .word dma1_c1_irq_handler
    .word dma1_c2_c3_irq_handler
    .word dma1_c4_c5_irq_handler
    .word adc1_irq_handler
    .word tim1_brk_up_trg_com_irq_handler
    .word tim1_cc_irq_handler
    .word 0
    .word tim3_irq_handler
    .word tim6_irq_handler
    .word tim7_irq_handler
    .word tim14_irq_handler
    .word tim15_irq_handler
    .word tim16_irq_handler
    .word tim17_irq_handler
    .word i2c1_irq_handler
    .word i2c2_irq_handler
    .word spi1_irq_handler
    .word spi2_irq_handler
    .word usart1_irq_handler
    .word usart2_irq_handler
    .word usart3_4_irq_handler
    .word 0
    .word usb_irq_handler

    // Weak aliases to default handler
    .weak nmi_handler
    .set nmi_handler, default_interrupt_handler

    .weak hard_fault_handler
    .set hard_fault_handler, default_interrupt_handler

    .weak svc_handler
    .set svc_handler, default_interrupt_handler

    .weak wwdg_irq_handler
    .set wwdg_irq_handler, default_interrupt_handler

    .weak rtc_irq_handler
    .set rtc_irq_handler, default_interrupt_handler

    .weak flash_irq_handler
    .set flash_irq_handler, default_interrupt_handler

    .weak rcc_irq_handler
    .set rcc_irq_handler, default_interrupt_handler

    .weak exti0_1_irq_handler
    .set exti0_1_irq_handler, default_interrupt_handler

    .weak exti2_3_irq_handler
    .set exti2_3_irq_handler, default_interrupt_handler

    .weak exti4_15_irq_handler
    .set exti4_15_irq_handler, default_interrupt_handler

    .weak dma1_c1_irq_handler
    .set dma1_c1_irq_handler, default_interrupt_handler

    .weak dma1_c2_c3_irq_handler
    .set dma1_c2_c3_irq_handler, default_interrupt_handler

    .weak dma1_c4_c5_irq_handler
    .set dma1_c4_c5_irq_handler, default_interrupt_handler

    .weak adc1_irq_handler
    .set adc1_irq_handler, default_interrupt_handler

    .weak tim1_brk_up_trg_com_irq_handler
    .set tim1_brk_up_trg_com_irq_handler, default_interrupt_handler

    .weak tim1_cc_irq_handler
    .set tim1_cc_irq_handler, default_interrupt_handler

    .weak tim3_irq_handler
    .set tim3_irq_handler, default_interrupt_handler

    .weak tim6_irq_handler
    .set tim6_irq_handler, default_interrupt_handler

    .weak tim7_irq_handler
    .set tim7_irq_handler, default_interrupt_handler

    .weak tim14_irq_handler
    .set tim14_irq_handler, default_interrupt_handler

    .weak tim15_irq_handler
    .set tim15_irq_handler, default_interrupt_handler

    .weak tim16_irq_handler
    .set tim16_irq_handler, default_interrupt_handler

    .weak tim17_irq_handler
    .set tim17_irq_handler, default_interrupt_handler

    .weak i2c1_irq_handler
    .set i2c1_irq_handler, default_interrupt_handler

    .weak i2c2_irq_handler
    .set i2c2_irq_handler, default_interrupt_handler

    .weak spi1_irq_handler
    .set spi1_irq_handler, default_interrupt_handler

    .weak spi2_irq_handler
    .set spi2_irq_handler, default_interrupt_handler

    .weak usart1_irq_handler
    .set usart1_irq_handler, default_interrupt_handler

    .weak usart2_irq_handler
    .set usart2_irq_handler, default_interrupt_handler

    .weak usart3_4_irq_handler
    .set usart3_4_irq_handler, default_interrupt_handler

    .weak usb_irq_handler
    .set usb_irq_handler, default_interrupt_handler
.size vtable, .-vtable


// Default interrupt handler
.section .text.default_interrupt_handler,"ax",%progbits
default_interrupt_handler:
    default_interrupt_loop:
        B default_interrupt_loop
.size default_interrupt_handler, .-default_interrupt_handler
