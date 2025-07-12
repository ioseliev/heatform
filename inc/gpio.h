#ifndef GPIO_H
#define GPIO_H

// Todos os endereços úteis do módulo de gpio
#define GPIO1			0x4804C000		// GPIO1 registers
#define GPIO_IRQSTATUS		(*(volatile unsigned int *)(GPIO1 + 0x2C))
#define GPIO_OE			(*(volatile unsigned int *)(GPIO1 + 0x134))
#define GPIO_CLEARDATAOUT	(*(volatile unsigned int *)(GPIO1 + 0x190))
#define GPIO_SETDATAOUT		(*(volatile unsigned int *)(GPIO1 + 0x194))
#define GPIO_IRQSTATUS_SET	(*(volatile unsigned int *)(GPIO1 + 0x34))
#define GPIO_IRQSTATUS_CLR	(*(volatile unsigned int *)(GPIO1 + 0x3C))
#define GPIO_RISINGDETECT	(*(volatile unsigned int *)(GPIO1 + 0x148))

// Protótipos das funções
void gpio1_rising_detect(int pin);
void gpio1_ack_interrupt(int pin);
void gpio1_interrupt_disable(int pin);
void gpio1_interrupt_enable(int pin);
void gpio1_output_enable(int pin);
void gpio1_cleardataout(int pin);
void gpio1_setdataout(int pin);

#endif
