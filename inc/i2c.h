#ifndef I2C_H
#define I2C_H

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

// Protótipo das funções
void i2c_disable_all_interrupts(void);
void i2c_master_enable(void);
void i2c_clock_config(void);
void i2c_reset_mode(void);
void i2c_interrupt_disable(void);
void i2c_interrupt_enable(void);
void mlx90614_send_read_command(unsigned char slave_addr, unsigned char reg_addr);
unsigned short mlx90614_read_word(unsigned char slave_addr);
float mlx90614_raw_to_celsius(unsigned short raw);
float mlx90614_read_temp(unsigned char reg);
float mlx90614_read_object_temp();
float mlx90614_read_ambient_temp();

#endif
