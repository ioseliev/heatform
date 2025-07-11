#define WDT_BASE              (*(volatile unsigned int*)0x44E35000)
#define WDT_WSPR              (*(volatile unsigned int*)0x44E35048)
#define WDT_WWPS              (*(volatile unsigned int*)0x44E35034)

// Protótipo das funções
void disable_wdt(void);

// As funções
void disable_wdt(void){
  	WDT_WSPR = 0xAAAA;
  	while((WDT_WWPS & (1<<4)));
  	WDT_WSPR = 0x5555;
  	while((WDT_WWPS & (1<<4)));
}
