#include "bool.h"
#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "eeprom_aa32af.h"
#include "oled_1602a.h"
#include "time.h"

void reset(void)
{
    oled_init();
    oled_display1("Booting up...");

    oled_display2("Testing EEPROM...");
    
    // TEST: EEPROM //
    eeprom_init(I2C_PORT_1);
    
    uint8_t write = 0xee;
    uint8_t dev_address = 0x57;
    uint16_t address = 0x0;
    
    oled_clear_display2();
    oled_display2("EEPROM: RAR");

    // TEST: Random-Access Read
    eeprom_flash_write(dev_address, address, write);
    uint8_t read = eeprom_flash_read(dev_address, address);
    if(read == write)
    {
        oled_display2("EEPROM: RAR pass");
    }
    else
    {
        oled_display2("EEPROM: RAR fail");
        return;
    }

    oled_clear_display2();
    oled_display2("EEPROM: SR");

    // TEST: Sequential Read
    eeprom_flash_write(dev_address, address + 0, 0xaa);
    eeprom_flash_write(dev_address, address + 1, 0xbb);
    eeprom_flash_write(dev_address, address + 2, 0xcc);
    eeprom_flash_write(dev_address, address + 3, 0xdd);
    uint8_t data[4] = {0};
    eeprom_flash_read_sequential(dev_address, address, data, sizeof(data));
    if(data[0] == 0xaa && data[1] == 0xbb && data[2] == 0xcc && data[3] == 0xdd)
    {
        oled_display2("EEPROM: SR pass");
    }
    else
    {
        oled_display2("EEPROM: SR fail");
        return;
    }
}

int STACK[256];

const void* vectors[] __attribute__((section(".vectors"))) = {
    STACK + sizeof(STACK) / sizeof(*STACK),
    reset
};