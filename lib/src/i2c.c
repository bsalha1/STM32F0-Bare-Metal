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