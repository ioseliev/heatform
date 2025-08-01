#include <__CONFIG__.h>
#include <state.h>
#include <canvas.h>

// Nossas bibliotecas
#include "cmper.h"
#include "controlmodule.h"
#include "gpio.h"
#include "i2c.h"
#include "intc.h"
#include "rtc.h"
#include "uart.h"
#include "watchdog.h"

// Variaveis globais
bool led_status = false;

// Funções auxiliares
void int_to_str(short int f,char *c);
void delay(int limite);	
void led_on(void);
void led_off(void);
void print_time(void);
void i2c_setup(void);
void gpio_setup(void);
void uart_setup(void);
void rtc_setup(void);
void IRQ_Handler(void);
void rtc_irq_handler(void);

static state global_state = {
	.target = TARGET_TEMP,
	.target_type = TARGET_TYPE,
	.target_reached = false,
	.temp_min = 1000.0f,
	.temp_max = -1000.0f,
};
static uint8_t canvas_buffer[CANVAS_LINE_LENGTH];


int main(void){
	canvas_init(canvas_buffer);
	
	char horas[100], minutos[100], segundos[100];

	gpio_setup();
	uart_setup();
	i2c_setup();
	disable_wdt();

	putString("\nQue horas são: ");
	getString(horas, sizeof(horas));

	putString("\nMinutos: ");
	getString(minutos, sizeof(minutos));

	putString("\nSegundos: ");
	getString(segundos, sizeof(segundos));

	putString("\nProjeto Final de TPSE I\n");

	rtc_setup();
	define_hour(horas);
	define_minute(minutos);
	define_second(segundos);

	while(1);
	return 0;
}

// As funções
void int_to_str(short int f,char *c){
    short int valor = f;
	short int aux, i = 0, j, start;
	char swap;

	if(valor == 0){
		c[i++] = '0';
		c[i] = '\0';
	}
	if(valor < 0){
		c[i++] = '-';
		valor = -valor;
	}

	start = i;
	while(valor > 0){
		aux = valor % 10;
		c[i++] = aux + '0';
		valor = valor / 10;
	}
	for(j = 0; j < (i - start)/2; j++){
		swap = c[start + j];
		c[start + j] = c[i - 1 - j];
		c[i - 1 - j] = swap;
	}

	c[i] = '\0';
}

void delay(int limite){
	int i;
	for(i = 0; i < limite; i++);
}

void led_on(void){
	gpio1_setdataout(21);
	led_status = false;
}

void led_off(void){
	gpio1_cleardataout(21);
	led_status = true;
}

void print_time(void){
  	unsigned char h,m,s;
	char temperatura[10];
	unsigned short int temp;

  	h = HOURS_REG;
  	m = MINUTES_REG;
  	s = SECONDS_REG;
  	putString("Hora: ");
  	//converte de BCD para ascii
  	//hora
  	putCh(0x30 + ((h >> 4) & 0x3)); //dezena
  	putCh(0x30 + ((h >> 0) & 0xf)); //unidade
  	putCh(':');
  	//minutos
  	putCh(0x30 + ((m >> 4) & 0x7)); //dezena
  	putCh(0x30 + ((m >> 0) & 0xf)); //unidade
   	putCh(':');
  	//segundos
  	putCh(0x30 + ((s >> 4) & 0x7)); //dezena
  	putCh(0x30 + ((s >> 0) & 0xf)); //unidade

	// temperatura
	temp = i2c_read_sensor();
	int_to_str(temp,temperatura);
	putString(" Temperatura: ");
	putString(temperatura);
	putString("°C");
	
  	putCh('\r');
	i2c_module_config();
}

void i2c_setup(void){
	i2c1_clock_enable();
	i2c1_pin_mux();
	i2c_module_config();
}

void gpio_setup(void){
	gpio1_clock_enable();
	gpio1_output_enable(21);
}

void uart_setup(void){
	uart0_clock_enable();
	uart0_pin_mux();
	uart0_config();
}

void rtc_setup(void){
	rtc_clock_enable();
	rtc_write_protection_disable();
	rtc_external_clock();
	rtc_interrupt_enable();
	start_rtc();
	intc_interrupt_rtc_accept();
}

void rtc_irq_handler(void){
	global_state.hours = HOURS_REG;
	global_state.minutes = MINUTES_REG;
	global_state.seconds = SECONDS_REG;
	
	global_state.temp = i2c_read_sensor();
	if ((global_state.target_type == LOW && global_state.temp <= global_state.target)
			|| (global_state.target_type == HIGH && global_state.temp >= global_state.target)) {
		global_state.target_reached = true;
		led_on();
	} else {
		global_state.target_reached = false;
		led_off();
	}

	// Software min/max bookkeeping
	if (global_state.temp < global_state.temp_min) {
		global_state.temp_min = global_state.temp;
	}
	if (global_state.temp > global_state.temp_max) {
		global_state.temp_max = global_state.temp;
	}
	
	canvas_update(canvas_buffer, &global_state, global_state.target_reached);
	putString((const char *) canvas_buffer);
}

void IRQ_Handler(void){
	unsigned int irq_number = (INTC_SIR_IRQ & 0x7f);
	if(irq_number == 75){
		rtc_irq_handler();
	}
	/* Reconhece a IRQ */
	INTC_CONTROL = 0x1;
}
