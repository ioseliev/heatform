#include "cmper.h"

#define CM_PER			0x44E00000		// Clock Module Peripheral Registers
#define CM_PER_GPIO1_CLKCTRL	(*(volatile unsigned int *)(CM_PER + 0xAC))
#define CM_PER_I2C2_CLKCTRL	(*(volatile unsigned int *)(CM_PER + 0x44))
#define CM_PER_I2C1_CLKCTRL	(*(volatile unsigned int *)(CM_PER + 0x48))

// As funções
void i2c1_clock_enable(void){
	CM_PER_I2C1_CLKCTRL = 0x2;
	while((CM_PER_I2C1_CLKCTRL & (0b11 << 16)) != 0);
}

void i2c2_clock_enable(void){
	CM_PER_I2C2_CLKCTRL = 0x2;
	while((CM_PER_I2C2_CLKCTRL & (0b11 << 16)) != 0);
}

void gpio1_clock_enable(void){
	CM_PER_GPIO1_CLKCTRL = 0x40002;
	while((CM_PER_GPIO1_CLKCTRL & (0b11 << 16)) != 0);
}
