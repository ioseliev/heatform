#include "rtc.h"

// As funções
void define_hour(char *n){
	unsigned char high, low;
	high = n[0] & 0x3;
	low = n[1] & 0xf;
	high = high << 4;
	high |= low;
	while(RTC_STATUS_REG & 0x1);
	HOURS_REG = high;
}

void define_minute(char *n){
	unsigned char high, low;
	high = n[0] & 0xf;
	low = n[1] & 0xf;
	high = high << 4;
	high |= low;
	while(RTC_STATUS_REG & 0x1);
	MINUTES_REG = high;
}

void define_second(char *n){
	unsigned char high, low;
	high = n[0] & 0x3;
	low = n[1] & 0xf;
	high = high << 4;
	high |= low;
	while(RTC_STATUS_REG & 0x1);
	SECONDS_REG = high;
}

void rtc_interrupt_enable(void){
	RTC_INTERRUPTS_REG = 0x4;
}

void rtc_external_clock(void){
	RTC_OSC_REG = 0x48;
}

void start_rtc(void){
	RTC_CTRL_REG |= 0x01;
}

void rtc_write_protection_disable(void){
	// Estamos desabilitando a proteção de escrita nos registradores RTC
	KICK0R = 0x83E70B13;
	KICK1R = 0x95A4F1E0;
}

void rtc_clock_enable(void){
	CM_RTC_CLKSTCTRL = 0x2;
	
	CM_RTC_RTC_CLKCTRL = 0x2;
	while((CM_RTC_RTC_CLKCTRL & (0b11 << 16)) != 0);
}
