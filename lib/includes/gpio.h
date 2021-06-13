#ifndef GPIO_H
#define GPIO_H

#include "int.h"
#include "bool.h"
#include "rcc.h"

struct gpio {
    uint32_t moder;   // GPIO port mode register
    uint32_t otyper;  // GPIO port output type register
    uint32_t ospeedr; // GPIO port output speed register
    uint32_t pupdr;   // GPIO port pull-up/pull-down register
    uint32_t idr;     // GPIO port input data register
    uint32_t odr;     // GPIO port output data register
    uint32_t bsrr;    // GPIO port bit set/reset register
    uint32_t lckr;    // GPIO port configuration lock register
    uint32_t afrl;    // GPIO alternate function low register
    uint32_t afrh;    // GPIO alternate function high register
    uint32_t brr;     // GPIO port bit reset register
};

#define GPIO_A ((volatile struct gpio *)0x48000000)
#define GPIO_B ((volatile struct gpio *)0x48000400)
#define GPIO_C ((volatile struct gpio *)0x48000800)
#define GPIO_D ((volatile struct gpio *)0x48000C00)
#define GPIO_E ((volatile struct gpio *)0x48001000)
#define GPIO_F ((volatile struct gpio *)0x48001400)

enum gpio_port {
    GPIO_PORT_A = 0,
    GPIO_PORT_B = 1,
    GPIO_PORT_C = 2,
    GPIO_PORT_D = 3,
    GPIO_PORT_E = 4, 
    GPIO_PORT_F = 5,
};

enum gpio_mode {
    MODE_INPUT = 0x00,
    MODE_OUTPUT = 0x01,
    MODE_ALTERNATE_FUNCTION = 0x02,
    MODE_ANALOG = 0x03,
};

/**
 * @brief Converts enum gpio_port to its structure
 * @param port GPIO port (A-F) to convert
 * @return Pointer to GPIO structure
 **/
volatile struct gpio* gpio_port_to_struct(enum gpio_port port);


/**
 * @brief Sets GPIO mode for given port and number
 * @param port GPIO port (A-F) to use
 * @param pin GPIO pin to use
 * @param mode GPIO mode to use
 **/
void set_gpio_mode(enum gpio_port port, uint8_t pin, enum gpio_mode mode);


/**
 * @brief Obtains current value of GPIO output
 * @param port GPIO port (A-F) to use
 * @param pin GPIO pin to use
 **/
unsigned int get_gpio_output(enum gpio_port port, uint8_t pin);


/**
 * @brief Sets value of GPIO output (1 or 0)
 * @param port GPIO port (A-F) to use
 * @param pin GPIO pin to use
 **/
void set_gpio_output(enum gpio_port port, uint8_t pin, bool value);


/**
 * @brief Enables GPIO
 * @param port GPIO port (A-F) to enable
 **/
void enable_gpio(enum gpio_port port);


/**
 * @brief Disables GPIO
 * @param port GPIO port (A-F) to disable
 **/
void disable_gpio(enum gpio_port port);


/**
 * @brief Sets alternate function to use on a GPIO port and pin
 * @param port GPIO port (A-F) to use
 * @param pin GPIO pin to use
 * @param function Alternate function to use (0-7)
 **/
void set_gpio_alternate_function(enum gpio_port port, uint8_t pin, uint8_t function);

#endif // GPIO_H