#ifndef RTC_H
#define RTC_H

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
