#include "eeprom_aa32af.h"
#include "os_assert.h"
#include "time.h"

void eeprom_init(enum i2c_port port)
{
    volatile struct i2c* i2c_slot;

    // PB5 AF3 = I2C1_SMBA
    if(port == I2C_PORT_1)
    {
        i2c_slot = I2C_1;
        enable_gpio(GPIO_PORT_B);

        // PA9 AF4 = I2C1_SCL
        // PA10 AF4 = I2C1_SDA

        // PB6 AF1 = I2C1_SCL
        // PB7 AF1 = I2C1_SDA
        
        // PB8 AF1 = I2C1_SCL
        // PB9 AF1 = I2C1_SDA
        
        // PF0 AF1 = I2C1_SDA
        // PF1 AF1 = I2C1_SCL

        set_gpio_mode(GPIO_PORT_B, 8, MODE_ALTERNATE_FUNCTION);
        set_gpio_mode(GPIO_PORT_B, 9, MODE_ALTERNATE_FUNCTION);
        set_gpio_alternate_function(GPIO_PORT_B, 8, 1);
        set_gpio_alternate_function(GPIO_PORT_B, 9, 1);

        enable_i2c(I2C_PORT_1);
    }
    else if(port == I2C_PORT_2)
    {
        i2c_slot = I2C_2;
        enable_gpio(GPIO_PORT_B);

        // PA11 AF4 = I2C2_SCL
        // PA12 AF4 = 12C2_SDA

        // PB10 AF1 = I2C2_SCL
        // PB11 AF1 = I2C2_SDA
        
        // PB13 AF5 = I2C2_SCL
        // PB14 AF5 = I2C2_SDA
        
        set_gpio_mode(GPIO_PORT_B, 10, MODE_ALTERNATE_FUNCTION);
        set_gpio_mode(GPIO_PORT_B, 11, MODE_ALTERNATE_FUNCTION);
        set_gpio_alternate_function(GPIO_PORT_B, 10, 1);
        set_gpio_alternate_function(GPIO_PORT_B, 11, 1);
    }

    

    // Disable channel
    i2c_slot->cr1 &= ~I2C_CR1_PE;


    // Configure channel
    i2c_slot->cr1 &= ~(I2C_CR1_ANFOFF | I2C_CR1_ERRIE | I2C_CR1_NOSTRETCH);

    // Configure clock
    i2c_slot->timingr = 0;
    i2c_slot->timingr |= 3 << 20; // SCLDEL = 3
    i2c_slot->timingr |= 1 << 16; // SCADEL = 1
    i2c_slot->timingr |= 9 << 0;  // SCLL = 9
    i2c_slot->timingr |= 3 << 8;  // SCLH = 3

    // Configure addressing
    i2c_slot->oar1 &= ~I2C_OAR1_OA1EN;
    i2c_slot->oar2 &= ~I2C_OAR2_OA2EN;
    i2c_slot->cr2 &= ~I2C_CR2_ADD10; // 7 bit addressing mode

    // Enable Channel
    i2c_slot->cr1 |= I2C_CR1_PE;
}

void eeprom_flash_write(uint8_t devaddr, uint16_t address, uint8_t data)
{
    if(address > MAX_ADDRESS)
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
    EEPROM_ASSERT(I2C_1->isr & I2C_ISR_NACKF == 0, "EEPROM: Unexpected NACK");

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;
	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
    
    small_sleep();
}

static void send_address(uint8_t devaddr, uint16_t address)
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
    EEPROM_ASSERT(I2C_1->isr & I2C_ISR_NACKF == 0, "EEPROM: Unexpected NACK");
}

uint8_t eeprom_flash_read(uint8_t devaddr, uint16_t address)
{   
    EEPROM_ASSERT(address <= MAX_ADDRESS, "EEPROM: Max address exceeded");
    
    // Send address without setting STOP bit
    send_address(devaddr, address);

    // Configure CR2 //
    uint32_t cr2 = I2C_1->cr2;
	cr2 &= ~(I2C_CR2_NBYTES);
	cr2 |= I2C_CR2_START | I2C_CR2_RD_WRN | ((1 << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = cr2;

    // Wait till RXDR not empty
    while((I2C_1->isr & I2C_ISR_RXNE) == 0);
    uint8_t data = I2C_1->rxdr & I2C_RXDR_RXDATA;
    
    // NACK must be received
    EEPROM_ASSERT(I2C_1->isr & I2C_ISR_NACKF != 0, "EEPROM: NACK expected");
    I2C_1->icr |= I2C_ICR_NACKCF;

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
	cr2 &= ~I2C_CR2_NBYTES;
	cr2 |= I2C_CR2_START | I2C_CR2_RD_WRN | ((data_length << 16) & I2C_CR2_NBYTES);
	I2C_1->cr2 = cr2;

    for(int i = 0; i < data_length; i++)
    {
        // Wait till RXDR not empty or for a NACK to be received
        while((I2C_1->isr & I2C_ISR_RXNE) == 0);

        // Read received byte
        data[i] = I2C_1->rxdr & I2C_RXDR_RXDATA;
    }

    // NACK must be received
    EEPROM_ASSERT(I2C_1->isr & I2C_ISR_NACKF != 0, "EEPROM: NACK expected");
    I2C_1->icr |= I2C_ICR_NACKCF;

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;
	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
    small_sleep();
}