#ifndef WATCHDOG_H
#define WATCHDOG_H

#define WDT_BASE              (*(volatile unsigned int*)0x44E35000)
#define WDT_WSPR              (*(volatile unsigned int*)0x44E35048)
#define WDT_WWPS              (*(volatile unsigned int*)0x44E35034)

// Protótipo das funções
void disable_wdt(void);

#endif
