#ifndef EEPROM_AA32AF_H
#define EEPROM_AA32AF_H

#include "int.h"
#include "i2c.h"

static int8_t send_address(uint8_t devaddr, uint16_t address);


void eeprom_init();


int8_t eeprom_flash_write(uint8_t devaddr, uint16_t address, uint8_t data);


uint8_t eeprom_flash_read(uint8_t devaddr, uint16_t address);

#endif // EEPROM_AA32AF_H