#include "i2c.h"

#define I2C1			0x4802A000					// I2C Registers
#define I2C_CON			(*(volatile unsigned int *)(I2C1 + 0xA4))		// I2C Configuration Register
#define I2C_CNT			(*(volatile unsigned int *)(I2C1 + 0x98))		// I2C Data Counter Register
#define I2C_SA			(*(volatile unsigned int *)(I2C1 + 0xAC))		// I2C Slave Address Register
#define	I2C_DATA		(*(volatile unsigned int *)(I2C1 + 0x9C))		// Data Access Register
#define I2C_IRQSTATUS		(*(volatile unsigned int *)(I2C1 + 0x28))		// I2C Status Register

#define I2C_PSC			(*(volatile unsigned int *)(I2C1 + 0xB0))		// I2C Clock Prescaler Register
#define I2C_SCLL		(*(volatile unsigned int *)(I2C1 + 0xB4))		// I2C SCL Low Time Register
#define I2C_SCLH		(*(volatile unsigned int *)(I2C1 + 0xB8))		// I2C SCL High Time Register
#define I2C_IRQENABLE_SET	(*(volatile unsigned int *)(I2C1 + 0x2C))		// I2C Interrupt Enable Set Register
#define I2C_IRQENABLE_CLR	(*(volatile unsigned int *)(I2C1 + 0x30))		// I2C Interrupt Enable Clear Register
#define I2C_SYSC		(*(volatile unsigned int *)(I2C1 + 0x10))		// System Configuration Register
#define I2C_SYSS		(*(volatile unsigned int *)(I2C1 + 0x90))		// System Status Register
#define I2C_BUF			(*(volatile unsigned int *)(I2C1 + 0x94))		// Buffer Configuration Register
#define I2C_WE			(*(volatile unsigned int *)(I2C1 + 0x34))		// I2C Wakeup Enable Register

// Outras macros
#define MLX90614_ADDR  0x5A
#define TEMP_OBJ_REG   0x07

// Funções
void i2c_interrupt_disable(void){
	// Desabilitar a interrupção
	I2C_IRQENABLE_CLR = (1 << 3);
}

void i2c_interrupt_enable(void){
	// Vamos habilitar a interrupção para quando o dado recebido
	I2C_IRQENABLE_SET = (1 << 3);
}

void i2c_write_reg(unsigned char slave_addr, unsigned char reg){
    I2C1_CNT = 1;
    I2C1_SA = slave_addr;
    I2C1_DATA = reg;

    I2C1_CON = (1 << 15) | // I2C_EN
               (1 << 10) | // Master mode
               (1 << 0)  | // Start
               (1 << 1);   // Stop

    while (!(I2C1_IRQSTATUS & (1 << 4))); // Espera TX completa
    I2C1_IRQSTATUS = (1 << 4);            // Limpa flag
}

unsigned short i2c_read_word(unsigned char slave_addr){
    I2C1_CNT = 3;         // 2 bytes de dados + 1 byte de PEC
    I2C1_SA = slave_addr;

    I2C1_CON = (1 << 15) | // I2C_EN
               (1 << 10) | // Master mode
               (1 << 0)  | // Start
               (1 << 1)  | // Stop
               (1 << 2);   // Read mode

    // LSB
    while (!(I2C1_IRQSTATUS & (1 << 3)));  // RRDY
    unsigned char lsb = I2C1_DATA;
    I2C1_IRQSTATUS = (1 << 3);

    // MSB
    while (!(I2C1_IRQSTATUS & (1 << 3)));  // RRDY
    unsigned char msb = I2C1_DATA;
    I2C1_IRQSTATUS = (1 << 3);

    // PEC (ignorar)
    while (!(I2C1_IRQSTATUS & (1 << 3)));
    volatile unsigned char pec = I2C1_DATA;
    I2C1_IRQSTATUS = (1 << 3);

    return ((unsigned short)msb << 8) | lsb;
}

float mlx90614_raw_to_celsius(unsigned short raw){
    return (raw * 0.02) - 273.15;
}

float read_temp_object(){
    i2c_write_reg(MLX90614_ADDR, TEMP_OBJ_REG);
    unsigned short raw = i2c_read_word(MLX90614_ADDR);
    return mlx90614_raw_to_celsius(raw);
}
