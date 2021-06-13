#include "rcc.h"
#include "gpio.h"
#include "spi.h"
#include "oled_1602a.h"

void oled_init()
{
    enable_gpio(GPIO_PORT_B);
    set_gpio_mode(GPIO_PORT_B, 12, MODE_ALTERNATE_FUNCTION);
    set_gpio_mode(GPIO_PORT_B, 13, MODE_ALTERNATE_FUNCTION);
    set_gpio_mode(GPIO_PORT_B, 15, MODE_ALTERNATE_FUNCTION);
    set_gpio_alternate_function(GPIO_PORT_B, 12, 0);
    set_gpio_alternate_function(GPIO_PORT_B, 13, 0);
    set_gpio_alternate_function(GPIO_PORT_B, 15, 0);
    
	enable_spi(SPI_PORT_2);

	SPI_2->cr1 |= SPI_CR1_MSTR | SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_BR;

	SPI_2->cr2 = (SPI_2->cr2 & ~SPI_CR2_DS) | (0x9 << 8) // 10 bit transfer size
        | SPI_CR2_NSSP | SPI_CR2_SSOE;

    // Enable SPI2
	SPI_2->cr1 |= SPI_CR1_SPE;

	for(int i = 0; i < 300000; i++);
	oled_cmd(0x38);
	oled_cmd(0x08);
	oled_cmd(0x01);
	for(int i = 0; i < 300000; i++);
	oled_cmd(0x06);
	oled_cmd(0x02);
	oled_cmd(0x0c);
}

static void oled_cmd(int cmd)
{
	// Wait Till Transmit Buffer Empty
	while((SPI_2->sr & SPI_SR_TXE) == 0);
	SPI_2->dr = cmd;
}

static void oled_data(int data)
{
	// Wait Till Transmit Buffer Empty
	while((SPI_2->sr & SPI_SR_TXE) == 0);
	SPI_2->dr = data | 0x200;
}

void oled_display1(const char * message)
{
	oled_cmd(0x02);
	int i = 0;
	while(message[i] != 0)
	{
		oled_data(message[i]);
		i++;
	}
}

void oled_display2(const char * message)
{
	oled_cmd(0xc0);
	int i = 0;
	while(message[i] != 0)
	{
		oled_data(message[i]);
		i++;
	}
}