#include "intc.h"

// As funções
void intc_interrupt_rtc_accept(void){
	INTC_MIR_CLEAR2 |= (1 << (75 - 64));
}

void intc_interrupt_i2c_accept(void){
	INTC_MIR_CLEAR2 |= (1 << (71 - 64));
}

void intc_interrupt_gpio_accept(void){
	INTC_MIR_CLEAR3 |= (1 << (98 - 96));
}

