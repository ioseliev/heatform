#include "i2c.h"
#include "uart.h"

// Funções
void espera(int tempo){
    int i;
    for(i = 0; i < tempo; i++);
}

void i2c_module_config(void){
    // Configurações iniciais do módulo i2c
    // Vamos desabilitá-lo e em seguida definirmos o valor do seu clock
    // Primeiro faremos um reset do Módulo i2c
    I2C_CON = 0;
    I2C_PSC  = 3;                   // Garante que o clock interno do módulo i2c será de 12MHz
    I2C_SCLL = 70;    
    I2C_SCLH = 50;
    I2C_OA = 0x000;
    I2C_CON = (1 << 15);
}

void i2c_interrupt_enable(int interrrupt){
	// Nesta função vamos habilitar interrupções de nosso interesse
    // São elas:
    // - No Acknowledgement Interrupt: Vai avisar quando um NACK ocorrer
    // - Start Condition Interrupt: Vai avisar quando uma condição de start ocorrer
    // - Bus Free Interrupt: Vai avisar quando o barramento do i2c está livre
    // - Transmit Data Ready Interrupt: Vai avisar quando um novo dado é requisitado (Quando o módulo está no modo receive)
    // - Receive Data Ready Interrupt: Vai avisar quando um novo dado está apto para ser lido.
	I2C_IRQENABLE_SET |= (1 << interrrupt);
}

void i2c_interrupt_disable(int interrupt){
	// Nesta função vamos desabilitar interrupções de nosso interesse
    // São elas:
    // - No Acknowledgement Interrupt: Vai avisar quando um NACK ocorrer
    // - Start Condition Interrupt: Vai avisar quando uma condição de start ocorrer
    // - Bus Free Interrupt: Vai avisar quando o barramento do i2c está livre
    // - Transmit Data Ready Interrupt: Vai avisar quando um novo dado é requisitado (Quando o módulo está no modo receive)
    // - Receive Data Ready Interrupt: Vai avisar quando um novo dado está apto para ser lido.
	I2C_IRQENABLE_CLR |= (1 << interrupt);
}

short int i2c_read_sensor(void){
    unsigned char msb, lsb, pec;                        // Vamos declarar duas variáveis de 8 bits para guardar respectivamente os bits mais e menos significantes
    short int data = 0;                                 // Retorno da função
    short int raw_data = 0;

    i2c_interrupt_enable(2);                            // Habilitar a interrupção ARDY
    
    I2C_SA = 0x5A;                                      // Vamos definir o Slave Address e enviar o bit de escrita
    I2C_CNT = 1;                                        // Um byte: comando
    I2C_DATA = 0x07;                                    // Comando para ler o TOBJ1
    // Definir o módulo como mestre, definir operação como transmissão e enviar a condição de start
    I2C_CON = (1 << 15) | (1 << 10) | (1 << 9) | (1 << 0);

   // putString("Definiu o slave address, que apenas um byte será enviado e qual registrador do sensor desejar ler\n");

    while(!(I2C_IRQSTATUS_RAW & (1 << 2)));             // Espera o ARDY (O bit enviado com o ACK)
    I2C_IRQSTATUS = 1 << 2;
    i2c_interrupt_disable(2);

    //putString("Habilitou a interrupção ARDY e esperou ela ser setada\n");

    I2C_CNT = 3;                                    // 2 dados + 1 PEC
    I2C_CON = (1 << 15) | (1 << 10) | (1 << 1) | (1 << 0);
    
    // putString("Define que 3 bytes serão lidos, habilita o módulo, define-o como mestre, ativa geração das condições de start e stop\n");

    i2c_interrupt_enable(3);
    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    lsb = I2C_DATA;
    I2C_IRQSTATUS = 1 << 3;

    // putString("Esperou que o byte menos significativo fosse enviado pelo sensor\n");

    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    msb = I2C_DATA;
    I2C_IRQSTATUS = 1 << 3;

    // putString("Esperou que o byte mais significativo fosse enviado pelo sensor\n");

    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    pec = I2C_DATA;
    I2C_IRQSTATUS = 1 << 3;

    // putString("No caso esperou que RRDY fosse disparada, tratou a interrupção, no caso leu o conteúdo da FIFO\n");

    i2c_interrupt_disable(3);

    raw_data = ((unsigned short)msb << 8) | (unsigned short)lsb;
    data = (raw_data / 50) - 273;
    I2C_SYSC = 0x2;
    return data;
}
