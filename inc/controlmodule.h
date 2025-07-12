#ifndef CONTROLMODULE_H
#define CONTROLMODULE_H

#define CONTROL_MODULE	0x44E10000						// Control Module Registers
#define CONF_UART0_RXD	(*(volatile unsigned int *)(CONTROL_MODULE + 0x970))
#define CONF_UART0_TXD	(*(volatile unsigned int *)(CONTROL_MODULE + 0x974))
#define CONF_MII1_CRS	(*(volatile unsigned int *)(CONTROL_MODULE + 0x90C))
#define CONF_MII1_RX_ER	(*(volatile unsigned int *)(CONTROL_MODULE + 0x910))

// Protótipos
void i2c1_pin_mux(void);
void uart0_pin_mux(void);

#endif
