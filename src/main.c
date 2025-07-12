#include <types.h>

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
int pow(int a, int b);
void reverse(char * str, int len);
int int_to_str(int x, char str[], int d);
void ftoa(float n, char *res, int afterpoint);
void led_on(void);
void led_off(void);
void print_temperature(void);
void print_time(void);
void i2c_setup(void);
void gpio_setup(void);
void uart_setup(void);
void rtc_setup(void);
void IRQ_Handler(void);
void rtc_irq_handler(void);
void i2c_irq_handler(void);

int main(void){
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
int pow(int a, int b){
	int i = 0, resposta = a;
	for(i = 0; i < b; i ++){
		resposta = resposta * a;
	}
	return resposta;
}

void ftoa(float n, char *res, int afterpoint){
	if(n < 0){
		*res ++ = '-';
		n = -n;
	}

	int ipart = (int)n;

	float fpart = n - (float)ipart;

	int i = int_to_str(ipart, res, 0);
	res[i] = '.'; // ponto

	fpart = fpart * pow(10, afterpoint);
	int_to_str((int)fpart, res + i + 1, afterpoint);
}

int int_to_str(int x, char str[], int d){
	int i = 0;
	if(x == 0){
		str[i++] = '0';
	}
	else{
		while(x){
			str[i] = (x%10) + '0';
			x /= 10;
			i++;
		}
	}
	while(i < d){
		str[i] = '0';
		i++;
	}
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}

void reverse(char * str, int len){
	int i = 0, j = len - 1;
	while(i < j){
		char t = str[i];
		str[i] = str[j];
		str[j] = t;
		i ++;
		j --;
	}
}

void led_on(void){
	gpio1_setdataout(21);
	led_status = false;
}

void led_off(void){
	gpio1_cleardataout(21);
	led_status = true;
}

void print_temperature(void){
	float ambiente;
	char buffer[100];

	ambiente = mlx90614_read_ambient_temp();
	//objeto = mlx90614_read_object_temp();

	ftoa(ambiente, buffer, 2);

	putString("Temperatura Atual:");
	putString(buffer);
	putString("°C\n");
}

void print_time(void){
  	unsigned char h,m,s;

  	h = HOURS_REG;
  	m = MINUTES_REG;
  	s = SECONDS_REG;
  	
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

  	putCh('\r');
}

void i2c_setup(void){
	i2c1_clock_enable();
	i2c1_pin_mux();
	//i2c_reset_mode(); // Tá dando problema
	i2c_clock_config();
	i2c_master_enable();
	i2c_disable_all_interrupts();
	intc_interrupt_i2c_accept();
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

void i2c_irq_handler(void){
	print_temperature();
}

void rtc_irq_handler(void){
	// Pisca o led
	((led_status) ? led_on() : led_off());

	// Imprime a hora
	print_time();
}

void IRQ_Handler(void){
	/* Verifica se é interrupção do RTC */
	unsigned int irq_number = (INTC_SIR_IRQ & 0x7f);
	if (irq_number == 75){
		rtc_irq_handler();
	}
	if(irq_number == 71){
		i2c_irq_handler();
	}

	/* Reconhece a IRQ */
	INTC_CONTROL = 0x1;
}
