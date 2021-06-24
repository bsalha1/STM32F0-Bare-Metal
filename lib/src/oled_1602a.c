#include "rcc.h"
#include "gpio.h"
#include "spi.h"
#include "oled_1602a.h"
#include "math.h"
#include <stdarg.h>

// Points to next index to put a char 
volatile uint8_t oled_char_pointer = 0;

void oled_init()
{
	oled_char_pointer = 0;
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
	oled_display_control(false, false, false);
	oled_clear_display();
	for(int i = 0; i < 300000; i++);
	oled_entry_mode_set(ENTRY_MODE_AUTO_INCREMENT, false);
	oled_return_home();
	oled_display_control(true, false, false);
}

static void oled_cmd(uint8_t cmd)
{
	// Wait Till Transmit Buffer Empty
	while((SPI_2->sr & SPI_SR_TXE) == 0);
	SPI_2->dr = cmd;
}

static void oled_data(uint16_t data)
{
	// Wait Till Transmit Buffer Empty
	while((SPI_2->sr & SPI_SR_TXE) == 0);
	SPI_2->dr = data | 0x200;
}

void oled_clear_display()
{
	oled_cmd(0x01);
}

void oled_return_home()
{
	oled_cmd(0x02);
}

void oled_entry_mode_set(enum entry_mode mode, bool shift_display)
{
	uint8_t cmd = 0x04;
	if(mode == ENTRY_MODE_AUTO_INCREMENT)
	{
		cmd |= 0x02;
	}

	if(shift_display)
	{
		cmd |= 0x01;
	}

	oled_cmd(cmd);
}

void oled_display_control(bool display_on, bool cursor_on, bool blinking_cursor)
{
	uint8_t cmd = 0x08;
	if(display_on)
	{
		cmd |= 0x04;
	}

	if(cursor_on)
	{
		cmd |= 0x02;
	}

	if(blinking_cursor)
	{
		cmd |= 0x01;
	}

	oled_cmd(cmd);
}

void oled_display_shift(enum display_type display_type, enum direction direction)
{
	uint8_t cmd = 0x10;

	if(display_type == DISPLAY_TYPE_SCREEN)
	{
		cmd |= 0x08;
	}

	if(direction == DIRECTION_RIGHT)
	{
		cmd |= 0x04;
	}

	oled_cmd(cmd);
}

void oled_set_ddram_address(uint8_t address)
{
	if((address > 0x0F && address < 0x40) || address > 0x4F)
	{
		// TODO: assert
		return;
	}
	oled_cmd(0x80 | address);
}

void oled_display1(const char * message)
{
	oled_return_home();
	int i = 0;
	while(message[i] != 0)
	{
		oled_data(message[i]);
		i++;
	}
}

void oled_display2(const char * message)
{
	oled_set_ddram_address(0x40); // Second line
	int i = 0;
	while(message[i] != 0)
	{
		oled_data(message[i]);
		i++;
	}
}

void oled_clear_display1()
{
	oled_display1("                ");
}

void oled_clear_display2()
{
	oled_display2("                ");
}

void oled_putchar_offset(char character, uint8_t offset)
{
	if(offset >= NUM_LINES * CHARACTERS_PER_LINE)
	{
		/// @todo assert
		return;
	}

	if(offset < CHARACTERS_PER_LINE)
	{
		oled_set_ddram_address(offset);
	}
	else
	{
		oled_set_ddram_address(0x40 + (offset - 16));
	}

	oled_data(character);
}

void oled_putchar(char character)
{
	oled_putchar_offset(character, oled_char_pointer);

	if(oled_char_pointer >= NUM_LINES * CHARACTERS_PER_LINE)
	{
		oled_char_pointer = 0;
	}
	else
	{
		oled_char_pointer++;
	}
}

void oled_puts(char* string)
{
	int i = 0;
	while(string[i] != 0)
	{
		oled_putchar(string[i]);
		i++;
	}
}

void oled_putint(uint32_t num) 
{
	int32_t power = 1;
	while(num > power)
    	power *= 10;

    power = divide(power, 10);

    while(num != 0)
    {
        int digit = divide(num, power);
		oled_putchar('0' + digit);
        if(digit != 0)
        	num = num - digit * power;

        if(power != 1)
        	power = divide(power, 10);
    }
}

void oled_printf(char* format,...) 
{ 
    char *traverse; 
    unsigned int i; 
    char *s; 

    va_list arg; 
    va_start(arg, format); 

    for(traverse = format; *traverse != '\0'; traverse++) 
    { 
        while(*traverse != '%') 
        { 
			if(*traverse == '\0')
			{
    			va_end(arg);
				return;
			}
            oled_putchar(*traverse);
            traverse++; 
        } 

        traverse++; 


        switch(*traverse)
        {
            case 'c': 
				i = va_arg(arg, int);
                oled_putchar(i);
                break;

            case 'd':
				i = va_arg(arg, int);
                if(i < 0)
				{ 
					i = -i;
					oled_putchar('-'); 
				}
				oled_putint(i);
				break;

            case 's': s = va_arg(arg, char *);
				oled_puts(s); 
				break;
        }
	}

    //Module 3: Closing argument list to necessary clean-up
    va_end(arg); 
} 