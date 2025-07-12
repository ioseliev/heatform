#ifndef UART_H
#define

// Protótipo das funções
void putCh(char c);
void putString(const char *str);
char getCh(void);
void getString(char *buffer, unsigned int length);
void uart0_config(void);
void uart0_clock_enable(void);

#endif
