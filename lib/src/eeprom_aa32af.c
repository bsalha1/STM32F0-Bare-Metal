#include "eeprom_aa32af.h"
#include "os_assert.h"
#include "time.h"

void eeprom_init()
{
    enable_gpio(GPIO_PORT_B);

    // PB8 AF1 = I2C_1_SCL
    // PB9 AF1 = I2C_1_SDA
    set_gpio_mode(GPIO_PORT_B, 8, MODE_ALTERNATE_FUNCTION);
    set_gpio_mode(GPIO_PORT_B, 9, MODE_ALTERNATE_FUNCTION);
    set_gpio_alternate_function(GPIO_PORT_B, 8, 1);
    set_gpio_alternate_function(GPIO_PORT_B, 9, 1);

    enable_i2c(I2C_PORT_1);

    // Disable channel
    I2C_1->cr1 &= ~I2C_CR1_PE;


    // Configure channel
    I2C_1->cr1 &= ~(I2C_CR1_ANFOFF | I2C_CR1_ERRIE | I2C_CR1_NOSTRETCH);

    // Configure clock
    I2C_1->timingr = 0;
    I2C_1->timingr |= 3 << 20; // SCLDEL = 3
    I2C_1->timingr |= 1 << 16; // SCADEL = 1
    I2C_1->timingr |= 9 << 0;  // SCLL = 9
    I2C_1->timingr |= 3 << 8;  // SCLH = 3

    // Configure addressing
    I2C_1->oar1 &= ~I2C_OAR1_OA1EN;
    I2C_1->oar2 &= ~I2C_OAR2_OA2EN;
    I2C_1->cr2 &= ~I2C_CR2_ADD10; // 7 bit addressing mode

    // Enable Channel
    I2C_1->cr1 |= I2C_CR1_PE;
}

int8_t eeprom_flash_write(uint8_t devaddr, uint16_t address, uint8_t data)
{
    if(address > 0xFFF)
    {
        // TODO: assert
    }

    uint8_t address_high_byte = (address & 0xFF00) >> 8;
    uint8_t address_low_byte = (address & 0x00FF);
    while((I2C_1->isr & I2C_ISR_BUSY) == I2C_ISR_BUSY);

    // Configure CR2 //
    uint32_t tmpreg = I2C_1->cr2;
	tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	tmpreg |= I2C_CR2_START | ((devaddr << 1) & I2C_CR2_SADD) | ((3 << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = tmpreg;


    // Send data
    while((I2C_1->isr & I2C_ISR_TXIS) == 0);
    I2C_1->txdr = address_high_byte & I2C_TXDR_TXDATA;

    while((I2C_1->isr & I2C_ISR_TXIS) == 0);
    I2C_1->txdr = address_low_byte & I2C_TXDR_TXDATA;

    while((I2C_1->isr & I2C_ISR_TXIS) == 0);
    I2C_1->txdr = data & I2C_TXDR_TXDATA;


    // Wait for transfer complete or for a NACK to be received from slave
    while((I2C_1->isr & I2C_ISR_TC) == 0 && (I2C_1->isr & I2C_ISR_NACKF) == 0);
    if((I2C_1->isr & I2C_ISR_NACKF) != 0)
    {
		I2C_1->icr |= I2C_ICR_NACKCF;
        ASSERT(false, "I2C: NACK recv");
        return -ENACK;
    }

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;
	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
    
    small_sleep();
}

static int8_t send_address(uint8_t devaddr, uint16_t address)
{
    uint8_t address_high_byte = (address & 0xFF00) >> 8;
    uint8_t address_low_byte = (address & 0x00FF);

    while((I2C_1->isr & I2C_ISR_BUSY) == I2C_ISR_BUSY);

    // Configure CR2 //
    uint32_t cr2 = I2C_1->cr2;
	cr2 &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD | I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
	cr2 |= I2C_CR2_START | ((devaddr << 1) & I2C_CR2_SADD) | ((2 << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = cr2;

    // Send data
    while((I2C_1->isr & I2C_ISR_TXIS) == 0);
    I2C_1->txdr = address_high_byte & I2C_TXDR_TXDATA;

    while((I2C_1->isr & I2C_ISR_TXIS) == 0);
    I2C_1->txdr = address_low_byte & I2C_TXDR_TXDATA;

    // Wait for transfer complete or for a NACK to be received
    while((I2C_1->isr & I2C_ISR_TC) == 0 && (I2C_1->isr & I2C_ISR_NACKF) == 0);
    if((I2C_1->isr & I2C_ISR_NACKF) != 0)
    {
		I2C_1->icr |= I2C_ICR_NACKCF;
        ASSERT(false, "I2C: NACK recv");
        return -ENACK;
    }
    return 0;
}

uint8_t eeprom_flash_read(uint8_t devaddr, uint16_t address)
{   
    if(address > 0xFFF)
    {
        // TODO: assert
    }
    
    // Send address without setting STOP bit
    send_address(devaddr, address);

    // Configure CR2 //
    uint32_t cr2 = I2C_1->cr2;
	cr2 &= ~(I2C_CR2_NBYTES);
	cr2 |= I2C_CR2_START | I2C_CR2_RD_WRN | ((1 << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = cr2;

    // Wait till RXDR not empty
    while((I2C_1->isr & I2C_ISR_RXNE) == 0);
    
    // NACK must be sent along with data
    if(I2C_1->isr & I2C_ISR_NACKF == 0)
    {
        ASSERT(false, "I2C: NACK expd");
        return 0;
    }
    I2C_1->icr |= I2C_ICR_NACKCF;

    // Read received byte
    uint8_t data = I2C_1->rxdr & I2C_RXDR_RXDATA;

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;
	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
    small_sleep();

    return data;
}

void eeprom_flash_read_sequential(uint8_t devaddr, uint16_t address, uint8_t* data, uint32_t data_length)
{
    // Send address without setting STOP bit
    send_address(devaddr, address);

    // Configure CR2 //
    uint32_t cr2 = I2C_1->cr2;
	cr2 &= ~(I2C_CR2_NBYTES);
	cr2 |= I2C_CR2_START | I2C_CR2_RD_WRN | ((data_length << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = cr2;

    for(int i = 0; i < data_length - 1; i++)
    {
        // Wait till RXDR not empty or for a NACK to be received
        while((I2C_1->isr & I2C_ISR_RXNE) == 0);

        // Read received byte
        data[i] = I2C_1->rxdr & I2C_RXDR_RXDATA;
    }

    // NACK must be sent at end of transfer
    while((I2C_1->isr & I2C_ISR_RXNE) == 0);
    if(I2C_1->isr & I2C_ISR_NACKF == 0)
    {
        ASSERT(false, "I2C: NACK expd");
        return;
    }
    I2C_1->icr |= I2C_ICR_NACKCF;

    // Read last received byte
    data[data_length - 1] = I2C_1->rxdr & I2C_RXDR_RXDATA;

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;
	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
    small_sleep();
}