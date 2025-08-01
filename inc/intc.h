#ifndef INTC_H
#define INTC_H

#define INTC			0x48200000		// Interrupt Controller Registers
#define INTC_SIR_IRQ		(*(volatile unsigned int *)(INTC + 0x40))
#define INTC_CONTROL		(*(volatile unsigned int *)(INTC + 0x48))
#define INTC_MIR_CLEAR2		(*(volatile unsigned int *)(INTC + 0xC8))
#define INTC_MIR_CLEAR3		(*(volatile unsigned int *)(INTC + 0xE8))

// Protótipo das funções
void intc_interrupt_rtc_accept(void);
void intc_interrupt_i2c_accept(void);
void intc_interrupt_gpio_accept(void);

#endif
