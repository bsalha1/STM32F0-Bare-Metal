#include "bool.h"
#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "eeprom_aa32af.h"
#include "oled_1602a.h"

void reset(void)
{
    oled_init();
    oled_display1("Booting up...");

    // EEPROM Test //
    oled_display2("Testing EEPROM...");
    
    uint8_t write = 0x21;
    uint16_t address = 0x200;
    eeprom_init(I2C_PORT_1);
    eeprom_flash_write(0x57, address, write);
    for(int i = 0; i < 50000; i++); // Wait
    uint8_t read = eeprom_flash_read(0x57, address);

    if(read == write)
    {
        oled_display2("EEPROM test passed");
    }
    else
    {
        oled_display2("EEPROM test failed!");
    }
}

int STACK[256];

const void* vectors[] __attribute__((section(".vectors"))) = {
    STACK + sizeof(STACK) / sizeof(*STACK),
    reset
};