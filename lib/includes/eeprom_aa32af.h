#ifndef EEPROM_AA32AF_H
#define EEPROM_AA32AF_H

/**
 * 4KB EEPROM http://ww1.microchip.com/downloads/en/devicedoc/22184a.pdf
 * 1 Page = 32B
 */

#include "int.h"
#include "i2c.h"

static int8_t send_address(uint8_t devaddr, uint16_t address);


void eeprom_init();


int8_t eeprom_flash_write(uint8_t devaddr, uint16_t address, uint8_t data);


uint8_t eeprom_flash_read(uint8_t devaddr, uint16_t address);


void eeprom_flash_read_sequential(uint8_t devaddr, uint16_t address, uint8_t* data, uint32_t data_length);

#endif // EEPROM_AA32AF_H