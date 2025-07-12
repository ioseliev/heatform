#include "uart.h"

// Funções
void putCh(char c){
	while(!(UART_LSR & (1 << 5)));
	UART_THR = c;
}

void putString(const char *str){
    while (*str) {
	if(*str == '\n')
		putCh('\r');
        putCh(*str++);
    }
}

char getCh(void){
	while(!(UART_LSR & (1<<0)));
	return UART_RHR;
}

void getString(char *buffer, unsigned int length){
	int i = 0;
	char c;
	while(i < length - 1){
		c = getCh();
		putCh(c);
		if(c == '\r' || c == '\n'){
			break;
		}
		buffer[i++] = c;
	}
	buffer[i] = '\0';
}

void uart0_config(void){
	UART_MDR1 = 0x7; // Coloca em modo de configuração
	
	UART_LCR = 0x83; // Coloca modo de acesso à divisor
	UART_DLL = 26; // Baudrate 115200 com clock de 48MHz : divisor = 26
	UART_DLH = 0;
	UART_LCR = 0x03; // Configura a UART com 8 bits, sem paridade, 1 stop bit
	UART_FCR = 0x07; // Habilita e limpa a FIFO 
	
	UART_MDR1 = 0x0;
}

void uart0_clock_enable(void){
	CM_WKUP_UART0_CLKCTRL = 0x2;
	while((CM_WKUP_UART0_CLKCTRL & (0b11 << 16)) != 0);
}
