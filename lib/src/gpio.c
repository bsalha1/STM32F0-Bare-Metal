#include "gpio.h"

volatile struct gpio* gpio_port_to_struct(enum gpio_port port)
{
    switch(port)
    {
        case GPIO_PORT_A: return GPIO_A;
        case GPIO_PORT_B: return GPIO_B;
        case GPIO_PORT_C: return GPIO_C;
        case GPIO_PORT_D: return GPIO_D;
        case GPIO_PORT_E: return GPIO_E;
        case GPIO_PORT_F: return GPIO_F;
        default: return 0x0;
    }
}

void set_gpio_mode(enum gpio_port port, uint8_t pin, enum gpio_mode mode)
{
    if(pin > 15)
    {
        // TODO: assert
        return;
    }

    volatile struct gpio* gpio = gpio_port_to_struct(port);

    gpio->moder &= ~(0x03 << (pin * 2));
    gpio->moder |= mode << (pin * 2);
}

unsigned int get_gpio_output(enum gpio_port port, uint8_t pin)
{
    if(pin > 15)
    {
        // TODO: assert
        return 0xFF;
    }

    volatile struct gpio* gpio = gpio_port_to_struct(port);

    return (gpio->odr & (1 << pin)) >> pin;
}

void set_gpio_output(enum gpio_port port, uint8_t pin, bool value)
{
    if(pin > 15)
    {
        // TODO: assert
        return;
    }

    volatile struct gpio* gpio = gpio_port_to_struct(port);

    if(value == 0)
    {
        gpio->odr &= ~(1 << pin);
    }
    else if(value == 1)
    {
        gpio->odr |= 1 << pin;
    }
    else
    {
        // TODO: assert
    }
}

void enable_gpio(enum gpio_port port)
{
    int gpio_en_offset = port; // Convert A -> 1, B -> 2, ...

    RCC->ahbenr |= 1 << (gpio_en_offset + 17); 
}

void disable_gpio(enum gpio_port port)
{
    int gpio_en_offset = port + 17;

    RCC->ahbenr &= ~(1 << gpio_en_offset); 
}

void set_gpio_alternate_function(enum gpio_port port, uint8_t pin, uint8_t function)
{
    if(function > 0x7)
    {
        // TODO: assert
        return;
    }

    if(pin > 15)
    {
        // TODO: assert
        return;
    }

    volatile struct gpio* gpio = gpio_port_to_struct(port);
    if(pin < 8)
    {
        gpio->afrl &=    ~(0xF << (pin * 4));
        gpio->afrl |= function << (pin * 4);
    }
    else
    {
        gpio->afrh  &=    ~(0xF << ((pin - 8) * 4));
        gpio->afrh  |= function << ((pin - 8) * 4);
    }
}