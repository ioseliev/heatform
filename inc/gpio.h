#ifndef GPIO_H
#define GPIO_H

// Protótipos das funções
void gpio1_rising_detect(int pin);
void gpio1_ack_interrupt(int pin);
void gpio1_interrupt_disable(int pin);
void gpio1_interrupt_enable(int pin);
void gpio1_output_enable(int pin);
void gpio1_cleardataout(int pin);
void gpio1_setdataout(int pin);

#endif
