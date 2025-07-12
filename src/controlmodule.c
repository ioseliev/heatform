#include "controlmodule.h"

#define CONTROL_MODULE	0x44E10000						// Control Module Registers
#define CONF_UART0_RXD	(*(volatile unsigned int *)(CONTROL_MODULE + 0x970))
#define CONF_UART0_TXD	(*(volatile unsigned int *)(CONTROL_MODULE + 0x974))
#define CONF_MII1_CRS	(*(volatile unsigned int *)(CONTROL_MODULE + 0x90C))
#define CONF_MII1_RX_ER	(*(volatile unsigned int *)(CONTROL_MODULE + 0x910))

// As funções
void i2c1_pin_mux(void){
	CONF_MII1_CRS |= 0x3;
	CONF_MII1_RX_ER |= 0x3;
}

void uart0_pin_mux(void){
	CONF_UART0_RXD |= 0x20;
	CONF_UART0_TXD |= 0x00;
}
