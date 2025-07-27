#ifndef CMPER_H
#define CMPER_H

#define CM_PER			        0x44E00000		// Clock Module Peripheral Registers
#define CM_PER_GPIO1_CLKCTRL	(*(volatile unsigned int *)(CM_PER + 0xAC))
#define CM_PER_I2C2_CLKCTRL	    (*(volatile unsigned int *)(CM_PER + 0x44))
#define CM_PER_I2C1_CLKCTRL	    (*(volatile unsigned int *)(CM_PER + 0x48))

// Os protótipos das funções 
void gpio1_clock_enable(void);
void i2c1_clock_enable(void);
void i2c2_clock_enable(void);

#endif
