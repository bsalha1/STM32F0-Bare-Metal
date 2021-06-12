// #include "gpio.h"

// void set_gpio_mode(enum gpio gpio_port, unsigned short gpio_num, enum mode gpio_mode)
// {
//     if(gpio_num > 15)
//     {
//         // TODO: assert
//         return;
//     }

//     unsigned int* gpio_address = gpio_to_address_table[gpio_port];
//     unsigned int* gpio_moder_address = gpio_address + MODER_OFFSET;
    
//     // *gpio_moder_address &= ~(0x03 << (gpio_num * 2));
//     *gpio_moder_address |= gpio_mode << (gpio_num * 2);
// }

// unsigned int get_gpio_output(enum gpio gpio_port, unsigned short gpio_num)
// {
//     if(gpio_num > 15)
//     {
//         // TODO: assert
//         return;
//     }

//     unsigned int* gpio_address = gpio_to_address_table[gpio_port];
//     unsigned int* gpio_odr_address = gpio_address + ODR_OFFSET;

//     return (*gpio_odr_address & (1 << (2 * gpio_num))) >> (2 * gpio_num);
// }

// void set_gpio_output(enum gpio gpio_port, unsigned short gpio_num, unsigned short value)
// {
//     if(gpio_num > 15)
//     {
//         // TODO: assert
//         return;
//     }

//     unsigned int* gpio_address = gpio_to_address_table[gpio_port];
//     unsigned int* gpio_odr_address = gpio_address + ODR_OFFSET;

//     if(value == 0)
//     {
//         *gpio_odr_address &= ~(1 << (gpio_num * 2));
//     }
//     else if(value == 1)
//     {
//         *gpio_odr_address |= 1 << (gpio_num * 2);
//     }
//     else
//     {
//         // TODO: assert
//     }
// }

// void enable_gpio(enum gpio gpio_port)
// {
//     int gpio_en_offset = gpio_port + 17;
//     unsigned int* rcc_ahbenr_address = RCC_AHBENR;

//     *rcc_ahbenr_address |= 1 << gpio_en_offset; 
// }

// void disable_gpio(enum gpio gpio_port)
// {
//     int gpio_en_offset = gpio_port + 17;
//     unsigned int* rcc_ahbenr_address = RCC_AHBENR;

//     *rcc_ahbenr_address &= ~(1 << gpio_en_offset); 
// }