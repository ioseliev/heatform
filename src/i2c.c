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
    I2C_CON = 0;
    I2C_PSC  = 3;
    I2C_SCLL = 60;    
    I2C_SCLH = 60;
    I2C_CON = (1 << 15);
}

void i2c_interrupt_enable(int interrrupt){
	// Nesta função vamos habilitar interrupções de nosso interesse
    // São elas:
    // - Bus Free Interrupt: Vai avisar quando o barramento do i2c está livre
    // - Transmit Data Ready Interrupt: Vai avisar quando um novo dado é requisitado (Quando o módulo está no modo receive)
    // - Receive Data Ready Interrupt: Vai avisar quando um novo dado está apto para ser lido.
	I2C_IRQENABLE_SET |= (1 << interrrupt);
}

void i2c_interrupt_disable(int interrupt){
	// Nesta função vamos desabilitar interrupções de nosso interesse
    // São elas:
    // - Bus Free Interrupt: Vai avisar quando o barramento do i2c está livre
    // - Transmit Data Ready Interrupt: Vai avisar quando um novo dado é requisitado (Quando o módulo está no modo receive)
    // - Receive Data Ready Interrupt: Vai avisar quando um novo dado está apto para ser lido.
	I2C_IRQENABLE_CLR &= ~(1 << interrupt);
}

unsigned short int i2c_read_sensor(void){
    unsigned char msb, lsb, pec;                     // Vamos declarar duas variáveis de 8 bits para guardar respectivamente os bits mais e menos significantes
    unsigned short int data = 0;                     // Retorno da função

    // Passo 1: Definir o endereço do Slave Device(SD) e o comando de leitura
    i2c_interrupt_enable(2);                        // ARDY_IE: Vamos habilitar essa interrupção para podermos verificar a disponibilidade dos registradores
    i2c_interrupt_enable(1);                        // NACK: Vamos habilitar essa interrupção para podermos checar se o bit NACK foi recebido e dessa forma repetirmos o processo até efetuarmos a comunicação
    I2C_IRQSTATUS = (1 << 12);                      // Liberar o barramento I2C
    do{
        I2C_SA = 0x5A;                              // Endereço Padrão do sensor (Default SA)
        I2C_CNT = 1;                                // Número de Bytes envolvidos na comunicação (1 byte)
        I2C_CON = (1 << 15) |                       // I2C_EN: Habilita o módulo I2C
                (1 << 10) |                         // MST: Define o módulo como mestre (MST = 1)
                (1 << 9)  |                         // TRX: Define a função do módulo como transmissor (TRX = 1)
                (1 << 1)  |                         // STP: Gera a condição de stop quando definido como 1   
                (1 << 0);                           // STT: Gera a condição de start quando definido como 1
        I2C_DATA = 0x06;                            // Esse é o comando que o sensor recebe, identifica e retorna o conteúdo do registrador relacionado
    }while(I2C_IRQSTATUS_RAW & (1 << 1));
    I2C_IRQSTATUS = (1 << 1);                       // Limpar a interrupção NACK
    while(!(I2C_IRQSTATUS & (1 << 2)));             // Poll para esperar que os registradores do I2C estejam prontos para serem acessados
    I2C_IRQSTATUS = (1 << 2);                       // Limpar a interrupção ARDY

    i2c_interrupt_enable(3);                        // RRDY: Vamos habilitar essa interrupção para sabermos que o dado solicitado foi recebido e está pronto para ser lido no I2C_DATA
    I2C_SA = 0x5A;                                  // Definir o endereço do SD que será lido
    I2C_CNT = 3;                                    // Vamos ler 3 bytes: MSB, LSB e PEC 
    I2C_CON = (1 << 15) |                           // I2C_EN: Habilitar o módulo I2C   
              (1 << 10) |                           // MST: Colocar o módulo em modo mestre  
              (0 << 9)  |                           // TRX: Definir módulo como receptor  
              (1 << 1)  |                           // STP: Gerar condição de stop
              (1 << 0);                             // STT: Gerar condição de start
    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    I2C_IRQSTATUS = (1 << 3);
    lsb = I2C_DATA;

    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    I2C_IRQSTATUS = (1 << 3);
    msb = I2C_DATA;

    while(!(I2C_IRQSTATUS_RAW & (1 << 3)));
    I2C_IRQSTATUS = (1 << 3);
    pec = I2C_DATA;

    i2c_interrupt_disable(3);
    i2c_interrupt_disable(2);
    i2c_interrupt_disable(1);
    data = ((unsigned short)msb << 8) | lsb;
    return data;
}
