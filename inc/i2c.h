#ifndef I2C_H
#define I2C_H

// Protótipo das funções
void i2c_interrupt_disable(void);
void i2c_interrupt_enable(void);
void i2c_write_reg(unsigned char slave_addr, unsigned char reg);
unsigned short i2c_read_word(unsigned char slave_addr);
float mlx90614_raw_to_celsius(unsigned short raw);
float read_temp_object();

#endif
