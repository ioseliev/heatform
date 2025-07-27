#ifndef RTC_H
#define RTC_H

#define CM_RTC			0x44E00800					// Clock Module RTC Registers
#define CM_RTC_RTC_CLKCTRL	(*(volatile unsigned int *)(CM_RTC + 0x00))
#define CM_RTC_CLKSTCTRL	(*(volatile unsigned int *)(CM_RTC + 0x04))

#define RTC			0x44E3E000					// RTC Registers
#define SECONDS_REG		(*(volatile unsigned int *)(RTC + 0x00))		// Seconds Register
#define MINUTES_REG		(*(volatile unsigned int *)(RTC + 0x04))		// Minutes Register
#define HOURS_REG		(*(volatile unsigned int *)(RTC + 0x08))		// Hours Register
#define RTC_CTRL_REG		(*(volatile unsigned int *)(RTC + 0x40))		// Control Register
#define RTC_STATUS_REG		(*(volatile unsigned int *)(RTC + 0x44))		// Status Register
#define RTC_INTERRUPTS_REG	(*(volatile unsigned int *)(RTC + 0x48))		// Interrupt Enable Register
#define RTC_OSC_REG		(*(volatile unsigned int *)(RTC + 0x54))		// Oscillator Register
#define KICK0R			(*(volatile unsigned int *)(RTC + 0x6C))		// Kick 0 Register (Write Protect)
#define KICK1R			(*(volatile unsigned int *)(RTC + 0x70))		// Kick 1 Register (Write Protect)

// Os protótipos das funções
void define_second(char *n);
void define_minute(char *n);
void define_hour(char *n);
void rtc_interrupt_enable(void);
void rtc_external_clock(void);
void start_rtc(void);
void rtc_write_protection_disable(void);
void rtc_clock_enable(void);

#endif
