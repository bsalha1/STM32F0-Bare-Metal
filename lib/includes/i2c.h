#ifndef I2C_H
#define I2C_H

#include "gpio.h"

#define I2C_CR1_PE        (1 << 0)
#define I2C_CR1_TXIE      (1 << 1) 
#define I2C_CR1_RXIE      (1 << 2)
#define I2C_CR1_ADDRIE    (1 << 3)
#define I2C_CR1_NACKIE    (1 << 4)
#define I2C_CR1_STOPIE    (1 << 5)
#define I2C_CR1_TCIE      (1 << 6)
#define I2C_CR1_ERRIE     (1 << 7)
#define I2C_CR1_ANFOFF    (1 << 12)
#define I2C_CR1_TXDMAEN   (1 << 14)
#define I2C_CR1_RXDMAEN   (1 << 15)
#define I2C_CR1_SBC       (1 << 16)
#define I2C_CR1_NOSTRETCH (1 << 17)

#define I2C_CR2_SADD     0x3FFF // 10 1's
#define I2C_CR2_RD_WRN  (1 << 10)
#define I2C_CR2_ADD10   (1 << 11)
#define I2C_CR2_HEAD10R (1 << 12)
#define I2C_CR2_START   (1 << 13)
#define I2C_CR2_STOP    (1 << 14)
#define I2C_CR2_NACK    (1 << 15)
#define I2C_CR2_NBYTES  (0xFF << 16)
#define I2C_CR2_RELOAD  (1 << 24)
#define I2C_CR2_AUTOEND (1 << 25)
#define I2C_CR2_PECBYTE (1 << 26)

#define I2C_OAR1_OA1EN (1 << 15)

#define I2C_OAR2_OA2EN (1 << 15)

#define I2C_ISR_TXIS  (1 << 1)
#define I2C_ISR_RXNE  (1 << 2)
#define I2C_ISR_NACKF (1 << 4)
#define I2C_ISR_STOPF (1 << 5)
#define I2C_ISR_TC    (1 << 6)
#define I2C_ISR_BUSY  (1 << 15)

#define I2C_ICR_NACKCF (1 << 4)
#define I2C_ICR_STOPCF (1 << 5)

#define I2C_TXDR_TXDATA 0xFF

#define I2C_RXDR_RXDATA 0xFF

struct i2c {
    uint32_t cr1;
    uint32_t cr2;
    uint32_t oar1;
    uint32_t oar2;
    uint32_t timingr;
    uint32_t timeoutr;
    uint32_t isr;
    uint32_t icr;
    uint32_t pecr;
    uint32_t rxdr;
    uint32_t txdr;
};

#define I2C_1 ((volatile struct i2c*)0x40005400)
#define I2C_2 ((volatile struct i2c*)0x40005800)

enum i2c_port {
    I2C_PORT_1 = 0,
    I2C_PORT_2 = 1
};

struct i2c_config {
    struct gpio_pin sda_1;
    struct gpio_pin scl_1;
    struct gpio_pin sda_2;
    struct gpio_pin scl_2;
};

void enable_i2c(enum i2c_port port);

#endif // I2C_H