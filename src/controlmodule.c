#include "controlmodule.h"

// As funções
void i2c1_pin_mux(void){
	conf_spi0_cs0 = 0x32;
	conf_spi0_d1 = 0x32;
}

void uart0_pin_mux(void){
	CONF_UART0_RXD = 0x20;
	CONF_UART0_TXD = 0x00;
}
