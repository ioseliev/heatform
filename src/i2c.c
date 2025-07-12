#include "i2c.h"

// Funções
void i2c_disable_all_interrupts(void){
    I2C_IRQSTATUS = 0xFFFF;
}

void i2c_master_enable(void){
    // Habita o módulo e ativa o modo mestre
    I2C_CON = (1 << 15) | (1 << 10);
}

void i2c_clock_config(void){
    I2C_PSC = 23;
    I2C_SCLL = 13;
    I2C_SCLH = 15;
}

void i2c_reset_mode(void){
    I2C_CON = 0x0;
    I2C_SYSC = 0x2;
    while((I2C_SYSS & 0x1) == 0);
}

void i2c_interrupt_disable(void){
	// Desabilitar a interrupção
	I2C_IRQENABLE_CLR = (1 << 3);
}

void i2c_interrupt_enable(void){
	// Vamos habilitar a interrupção para quando o dado recebido
	I2C_IRQENABLE_SET = (1 << 3);
}

void mlx90614_send_read_command(unsigned char slave_addr, unsigned char reg_addr){
    I2C_CNT = 1;
    I2C_SA  = slave_addr;
    I2C_DATA = reg_addr;

    I2C_CON = (1 << 15) | // I2C_EN
               (1 << 10) | // Master mode
               (1 << 9)  | // Transmit mode
               (1 << 1)  | // Stop condition
               (1 << 0);   // Start condition

    while (!(I2C_IRQSTATUS & (1 << 4))); // XRDY
    I2C_IRQSTATUS = (1 << 4);            // Limpa flag
}

unsigned short mlx90614_read_word(unsigned char slave_addr){
    I2C_CNT = 3;            // 2 dados + 1 PEC
    I2C_SA  = slave_addr;

    I2C_CON = (1 << 15) |   // I2C_EN
               (1 << 10) |   // Master mode
               (0 << 9)  |   // Receive mode
               (1 << 1)  |   // Stop
               (1 << 0)  |   // Start
               (1 << 2);     // Read

    // LSB
    while (!(I2C_IRQSTATUS & (1 << 3))); // RRDY
    unsigned char lsb = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

    // MSB
    while (!(I2C_IRQSTATUS & (1 << 3)));
    unsigned char msb = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

    // PEC (ignorar)
    while (!(I2C_IRQSTATUS & (1 << 3)));
    volatile unsigned char pec = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

    return ((unsigned short)msb << 8) | lsb;
}

float mlx90614_raw_to_celsius(unsigned short raw){
    return (raw * 0.02f) - 273.15f;
}

float mlx90614_read_temp(unsigned char reg){
    mlx90614_send_read_command(0x5A, reg);
    unsigned short raw = mlx90614_read_word(0x5A);
    return mlx90614_raw_to_celsius(raw);
}

float mlx90614_read_object_temp(){
    return mlx90614_read_temp(0x07);
}

float mlx90614_read_ambient_temp(){
    return mlx90614_read_temp(0x06);
}
