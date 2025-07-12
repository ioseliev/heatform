#include "i2c.h"

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
    I2C_CNT = 1;
    I2C_SA = slave_addr;
    I2C_DATA = reg;

    I2C_CON = (1 << 15) | // I2C_EN
               (1 << 10) | // Master mode
               (1 << 0)  | // Start
               (1 << 1);   // Stop

    while (!(I2C_IRQSTATUS & (1 << 4))); // Espera TX completa
    I2C_IRQSTATUS = (1 << 4);            // Limpa flag
}

unsigned short i2c_read_word(unsigned char slave_addr){
    I2C_CNT = 3;         // 2 bytes de dados + 1 byte de PEC
    I2C_SA = slave_addr;

    I2C_CON = (1 << 15) | // I2C_EN
               (1 << 10) | // Master mode
               (1 << 0)  | // Start
               (1 << 1)  | // Stop
               (1 << 2);   // Read mode

    // LSB
    while (!(I2C_IRQSTATUS & (1 << 3)));  // RRDY
    unsigned char lsb = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

    // MSB
    while (!(I2C_IRQSTATUS & (1 << 3)));  // RRDY
    unsigned char msb = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

    // PEC (ignorar)
    while (!(I2C_IRQSTATUS & (1 << 3)));
    volatile unsigned char pec = I2C_DATA;
    I2C_IRQSTATUS = (1 << 3);

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
