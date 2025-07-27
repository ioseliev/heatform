#ifndef UART_H
#define UART_H

#define CM_WKUP			0x44E00400					// Control Module Wakeup Registers
#define CM_WKUP_UART0_CLKCTRL	(*(volatile unsigned int *)(UART0 + 0xB4))

#define UART0			0x44E09000					// UART Registers
#define UART_THR		(*(volatile unsigned int *)(UART0 + 0x0)) 	// Transmit Holding Register
#define UART_RHR		(*(volatile unsigned int *)(UART0 + 0x0)) 	// Receiver Holding Register
#define UART_LSR		(*(volatile unsigned int *)(UART0 + 0x14)) 	// Line Status Register

#define UART_LCR		(*(volatile unsigned int *)(UART0 + 0xC))	// Line Control Register
#define UART_DLL		(*(volatile unsigned int *)(UART0 + 0x0))	// Divisor Latches Low Register
#define UART_DLH		(*(volatile unsigned int *)(UART0 + 0x4))	// Divisor Latches High Register
#define UART_FCR		(*(volatile unsigned int *)(UART0 + 0x8))	// FIFO Control Register
#define UART_MDR1		(*(volatile unsigned int *)(UART0 + 0x20))	// Mode Definition Register 1

// Protótipo das funções
void putCh(char c);
void putString(const char *str);
char getCh(void);
void getString(char *buffer, unsigned int length);
void uart0_config(void);
void uart0_clock_enable(void);

#endif
