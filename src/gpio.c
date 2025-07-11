// Todos os endereços úteis do módulo de gpio
#define GPIO1			0x4804C000		// GPIO1 registers
#define GPIO_IRQSTATUS		(*(volatile unsigned int *)GPIO1 + 0x2C)
#define GPIO_OE			(*(volatile unsigned int *)GPIO1 + 0x134)
#define GPIO_CLEARDATAOUT	(*(volatile unsigned int *)GPIO1 + 0x190)
#define GPIO_SETDATAOUT		(*(volatile unsigned int *)GPIO1 + 0x194)
#define GPIO_IRQSTATUS_SET	(*(volatile unsigned int *)GPIO1 + 0x34)
#define GPIO_IRQSTATUS_CLR	(*(volatile unsigned int *)GPIO1 + 0x3C)
#define GPIO_RISINGDETECT	(*(volatile unsigned int *)GPIO1 + 0x148)

#define INTC			0x48200000		// Interrupt Controller Registers
#define INTC_SIR_IRQ		(*(volatile unsigned int *)INTC + 0x40)
#define INTC_CONTROL		(*(volatile unsigned int *)INTC + 0x48)
#define INTC_MIR_CLEAR3		(*(volatile unsigned int *)INTC + 0xE8)


// Protótipos das funções
void gpio1_rising_detect(int pin);
void intc_ack_interrupt(int pin);
void intc_interrupt_gpio_accept(void);
void gpio1_interrupt_disable(int pin);
void gpio1_interrupt_enable(int pin);
void gpio1_output_enable(int pin);
void gpio1_cleardataout(int pin);
void gpio1_setdataout(int pin);

// As funções propriamente ditas
void gpio1_rising_detect(int pin){
	GPIO_RISINGDETECT |= (1 << pin);
}

void gpio1_ack_interrupt(int pin){
	GPIO_IRQSTATUS = (1 << pin);
}

void intc_interrupt_gpio_accept(void){
	INTC_MIR_CLEAR3 |= (1 << (98 - 96))
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
