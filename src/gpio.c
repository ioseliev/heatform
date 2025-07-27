#include "gpio.h"

// As funções propriamente ditas
void gpio1_rising_detect(int pin){
	GPIO_RISINGDETECT |= (1 << pin);
}

void gpio1_ack_interrupt(int pin){
	GPIO_IRQSTATUS = (1 << pin);
}

void gpio1_interrupt_disable(int pin){
	GPIO_IRQSTATUS_CLR = (1 << pin);
}

void gpio1_interrupt_enable(int pin){
	GPIO_IRQSTATUS_SET |= (1 << pin);
}

void gpio1_output_enable(int pin){
	// o pino passado como entrada será definido como saida
	GPIO_OE &= ~(1 << pin);
}

void gpio1_cleardataout(int pin){
	GPIO_CLEARDATAOUT = (1 << pin);
}

void gpio1_setdataout(int pin){
	GPIO_SETDATAOUT = (1 << pin);
}