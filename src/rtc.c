#define CM_RTC			0x44E00800					// Clock Module RTC Registers
#define CM_RTC_RTC_CLKCTRL	(*(volatile unsigned int *)CM_RTC + 0x00)
#define CM_RTC_CLKSTCTRL	(*(volatile unsigned int *)CM_RTC + 0x04)

#define RTC			0x0x44E3_E000					// RTC Registers
#define SECONDS_REG		(*(volatile unsigned int *)RTC + 0x00)		// Seconds Register
#define MINUTES_REG		(*(volatile unsigned int *)RTC + 0x04)		// Minutes Register
#define HOURS_REG		(*(volatile unsigned int *)RTC + 0x08)		// Hours Register
#define RTC_CTRL_REG		(*(volatile unsigned int *)RTC + 0x40)		// Control Register
#define RTC_STATUS_REG		(*(volatile unsigned int *)RTC + 0x44)		// Status Register
#define RTC_INTERRUPTS_REG	(*(volatile unsigned int *)RTC + 0x48)		// Interrupt Enable Register
#define RTC_OSC_REG		(*(volatile unsigned int *)RTC + 0x54)		// Oscillator Register
#define KICK0R			(*(volatile unsigned int *)RTC + 0x6C)		// Kick 0 Register (Write Protect)
#define KICK1R			(*(volatile unsigned int *)RTC + 0x70)		// Kick 1 Register (Write Protect)

// Os protótipos das funções
void define_second(char *n);
void define_minute(char *n);
void define_hour(char *n);
void rtc_interrupt_enable(void);
void rtc_external_clock(void);
void start_rtc(void);
void rtc_write_protection_disable(void);
void rtc_clock_enable(void);

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
	high = n[0] & 0x3;
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
