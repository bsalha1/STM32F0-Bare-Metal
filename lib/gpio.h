#ifndef GPIO_H
#define GPIO_H

#include "rcc.h"

#define GPIOA 0x48000000
#define GPIOB 0x48000400
#define GPIOC 0x48000800
#define GPIOD 0x48000C00
#define GPIOE 0x48001000
#define GPIOF 0x48001400

#define MODER_OFFSET 0x00
#define ODR_OFFSET 0x14

enum gpio {
    GPIO_A = GPIOA, 
    GPIO_B = GPIOB, 
    GPIO_C = GPIOC, 
    GPIO_D = GPIOD, 
    GPIO_E = GPIOE, 
    GPIO_F = GPIOF
};

enum mode {
    MODE_INPUT = 0x00,
    MODE_OUTPUT = 0x01,
    MODE_ALTERNATE_FUNCTION = 0x02,
    MODE_ANALOG = 0x03,
};

void set_gpio_mode(enum gpio gpio_port, unsigned short gpio_num, enum mode gpio_mode)
{
    if(gpio_num > 15)
    {
        // TODO: assert
        return;
    }

    unsigned int* gpio_moder_address = (unsigned int*) (gpio_port + MODER_OFFSET);
    
    // *gpio_moder_address &= ~(0x03 << (gpio_num * 2));
    *gpio_moder_address |= gpio_mode << (gpio_num * 2);
}

unsigned int get_gpio_output(enum gpio gpio_port, unsigned short gpio_num)
{
    if(gpio_num > 15)
    {
        // TODO: assert
        return 0xFF;
    }

    unsigned int* gpio_odr_address = (unsigned int*) (gpio_port + ODR_OFFSET);

    return (*gpio_odr_address & (1 << gpio_num)) >> gpio_num;
}

void set_gpio_output(enum gpio gpio_port, unsigned short gpio_num, unsigned short value)
{
    if(gpio_num > 15)
    {
        // TODO: assert
        return;
    }

    unsigned int* gpio_odr_address = (unsigned int*) (gpio_port + ODR_OFFSET);

    if(value == 0)
    {
        *gpio_odr_address &= ~(1 << gpio_num);
    }
    else if(value == 1)
    {
        *gpio_odr_address |= 1 << gpio_num;
    }
    else
    {
        // TODO: assert
    }
}

void enable_gpio(enum gpio gpio_port)
{
    int gpio_en_offset = (gpio_port - 0x48000000) / 0x400; // Convert A -> 1, B -> 2, ...
    unsigned int* rcc_ahbenr_address = (unsigned int*)RCC_AHBENR;

    *rcc_ahbenr_address |= 1 << (gpio_en_offset + 17); 
}

void disable_gpio(enum gpio gpio_port)
{
    int gpio_en_offset = gpio_port + 17;
    unsigned int* rcc_ahbenr_address = (unsigned int*)RCC_AHBENR;

    *rcc_ahbenr_address &= ~(1 << gpio_en_offset); 
}

#endif // GPIO_H