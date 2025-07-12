#include "intc.h"

#define INTC			0x48200000		// Interrupt Controller Registers
#define INTC_SIR_IRQ		(*(volatile unsigned int *)INTC + 0x40)
#define INTC_CONTROL		(*(volatile unsigned int *)INTC + 0x48)
#define INTC_MIR_CLEAR2		(*(volatile unsigned int *)INTC	+ 0xC8)
#define INTC_MIR_CLEAR3		(*(volatile unsigned int *)INTC + 0xE8)

// As funções
void intc_interrupt_rtc_accept(void){
	INTC_MIR_CLEAR2 |= (1 << (75 - 64));
}

void intc_interrupt_i2c_accept(void){
	INTC_MIR_CLEAR2 |= (1 << (71 - 64));
}

void intc_interrupt_gpio_accept(void){
	INTC_MIR_CLEAR3 |= (1 << (98 - 96))
}
