#include "i2c.h"
#include "gpio.h"

void enable_i2c(enum i2c_port port)
{
	if(port == I2C_PORT_1)
	{
    	RCC->apb1enr |= 1 << 21;
	}
	else if(port == I2C_PORT_2)
	{
    	RCC->apb1enr |= 1 << 22;
	}
	else
	{
		// TODO: assert
	}
}

void i2c_start(uint32_t devaddr, uint8_t size, uint8_t dir)
{
	uint32_t tmpreg = I2C_1->cr2;
	tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD |
            I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START |
			I2C_CR2_STOP);

	if(dir == 1) // Read
	{
		tmpreg |= I2C_CR2_RD_WRN;
	}
	else // Write
	{
		tmpreg &= ~I2C_CR2_RD_WRN;
	}

	tmpreg |= ((devaddr << 1) & I2C_CR2_SADD) | ((size << 16) & I2C_CR2_NBYTES);
	tmpreg |= I2C_CR2_START;
	I2C_1->cr2 = tmpreg;
}

void i2c_stop(void)
{
	if(I2C_1->isr & I2C_ISR_STOPF)
	{
		return;
	}

	// Generate stop bit
	I2C_1->cr2 |= I2C_CR2_STOP;

	// Wait until STOPF flag is reset then clear it
	while((I2C_1->isr & I2C_ISR_STOPF) == 0);
	I2C_1->icr |= I2C_ICR_STOPCF;
}

void i2c_waitidle(void)
{
	// Wait until not busy
	while((I2C_1->isr & I2C_ISR_BUSY) == I2C_ISR_BUSY);
}

int8_t i2c_handshake(uint8_t devaddr)
{
    while((I2C_1->isr & I2C_ISR_BUSY) == I2C_ISR_BUSY);

    uint32_t tmpreg = I2C_1->cr2;
	tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES | I2C_CR2_RELOAD |
            I2C_CR2_AUTOEND | I2C_CR2_RD_WRN | I2C_CR2_START |
			I2C_CR2_STOP);

	tmpreg |= (devaddr << 1) & I2C_CR2_SADD;

    // Generate START bit
	tmpreg |= I2C_CR2_START;
	I2C_1->cr2 = tmpreg;

    // Generate STOP bit
	I2C_1->cr2 |= I2C_CR2_STOP;

	while((I2C_1->isr & I2C_ISR_STOPF) == 0); // Wait till STOP detected
	I2C_1->icr |= I2C_ICR_STOPCF; // Clear STOPF in ISR
}

int8_t i2c_senddata(uint8_t devaddr, void *pdata, uint8_t size)
{
	if(size <= 0 || pdata == 0)
	{
		return -4;
	}

	uint8_t *udata = (uint8_t*) pdata;

	while((I2C_1->isr & I2C_ISR_BUSY) == I2C_ISR_BUSY);
	i2c_start(devaddr, 0, 0);


	return 0;
}

uint8_t i2c_recvdata(uint8_t devaddr, uint8_t *pdata, uint8_t size)
{
	if(size <= 0 || pdata == 0x0)
	{
		return -1;
	}

	i2c_waitidle();
	i2c_start(devaddr, size, 1);

	int i;
	for(i = 0; i < size; i++)
	{
		while((I2C_1->isr & I2C_ISR_RXNE) == 0);
		pdata[i] = I2C_1->rxdr & I2C_RXDR_RXDATA;
	}
	while((I2C_1->isr & I2C_ISR_TC) == 0);

	i2c_stop();
	return 0;
}

void i2c_write_flash(uint16_t loc, const char *data, uint8_t len)
{
	uint8_t buffer[34];
	buffer[0] = (loc & 0xFF00) >> 8; // High byte
	buffer[1] = loc & 0x00FF;        // Low byte

	int i;
	for(i = 0; i < len && i < 32; i++)
	{
		buffer[2 + i] = data[i];
	}

	i2c_senddata(0x57, buffer, len + 2);
}

int i2c_write_flash_complete()
{
	i2c_waitidle();
	i2c_start(0x57, 0, 0);

	while((I2C_1->isr & I2C_ISR_TC) == 0 && (I2C_1->isr & I2C_ISR_NACKF) == 0);
	if((I2C_1->isr & I2C_ISR_NACKF) != 0)
	{
		I2C_1->icr |= I2C_ICR_NACKCF;
		i2c_stop();
		return 0;
	}
	else
	{
		i2c_stop();
		return 1;
	}

	return 0;
}

void i2c_set_gpio(int value)
{
	uint8_t data[] = {0x09, value};
	i2c_senddata(0x27, data, sizeof(data));
}

void i2c_read_flash(uint16_t loc, char data[], uint8_t len)
{
	uint8_t read_request[] = {(loc & 0xFF00) >> 8, loc & 0x00FF};
	i2c_senddata(0x57, read_request, sizeof(read_request));

	// i2c_recvdata(0x57, data, len);
}