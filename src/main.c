#include <stdbool.h>

// Nossas bibliotecas
#include "gpio.h"
#include "uart.h"
#include "rtc.h"
#include "i2c.h"

// Variaveis globais
bool led_status = false;

// Funções auxiliares
void delay(int max);
void led_blink();

int main(void){
	while(1);
	return 0;
}
