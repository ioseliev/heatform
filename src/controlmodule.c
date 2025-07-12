#include "controlmodule.h"

// As funções
void i2c1_pin_mux(void){
	CONF_MII1_CRS |= 0x3;
	CONF_MII1_RX_ER |= 0x3;
}

void uart0_pin_mux(void){
	CONF_UART0_RXD |= 0x20;
	CONF_UART0_TXD |= 0x00;
}
