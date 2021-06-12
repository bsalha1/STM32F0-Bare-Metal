#include "lib/bool.h"
// #include "lib/rcc.h"
#include "lib/gpio.h"

void reset(void)
{
    volatile unsigned int* rcc_ahbenr  = 0x40021000 + 0x14;
    volatile unsigned int* gpioc_moder = 0x48000800 + 0x00;
    volatile unsigned int* gpioc_odr   = 0x48000800 + 0x14;

    enable_gpio(GPIO_C);
    set_gpio_mode(GPIO_C, 13, MODE_OUTPUT);
    while(1)
    {
        unsigned int current_output = get_gpio_output(GPIO_C, 13);
        set_gpio_output(GPIO_C, 13, 1 ^ current_output);

        for(int i = 0; i < 500000; i++); // Wait
    }
}

int STACK[256];

const void* vectors[] __attribute__((section(".vectors"))) = {
    STACK + sizeof(STACK) / sizeof(*STACK),
    reset
};