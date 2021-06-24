#ifndef EEPROM_AA32AF_H
#define EEPROM_AA32AF_H

/**
 * This is a driver for a 4KB EEPROM http://ww1.microchip.com/downloads/en/devicedoc/22184a.pdf
 * 1 Page = 32 Bytes
 */

#include "int.h"
#include "i2c.h"
#include "os_assert.h"

#define MAX_ADDRESS 0xFFF
#define EEPROM_ASSERT(cond, message) OS_ASSERT(cond, message)


/**
 * @brief Initializes EEPROM to run on given I2C port
 * @param port The I2C port to run on
 */
void eeprom_init(enum i2c_port port);


/**
 * @brief Writes data to EEPROM memory
 * @param devaddr I2C address of device
 * @param address Address in EEPROM memory to write to
 * @param data Data to write to EEPROM memory
 */
void eeprom_flash_write(uint8_t devaddr, uint16_t address, uint8_t data);


/**
 * @brief Sends address to read from without a STOP. Used by eeprom_flash_read to tell chip which address to read from.
 * @param devaddr I2C address of device
 * @param address Address in EEPROM memory to send
 */
static void send_address(uint8_t devaddr, uint16_t address);


/**
 * @brief Reads one byte at EEPROM address
 * @param devaddr I2C address of device
 * @param address Address in EEPROM memory to read from
 * @return Value of byte read
 */
uint8_t eeprom_flash_read(uint8_t devaddr, uint16_t address);


/**
 * @brief Reads bytes starting from (address) to (address + data_length - 1) and puts into data
 * @param devaddr I2C address of device
 * @param address Address in EEPROM memory to start reading from
 * @param data Buffer to put read bytes into
 * @param data_length Number of bytes to read & number of ints allocated for data pointer
 */
void eeprom_flash_read_sequential(uint8_t devaddr, uint16_t address, uint8_t* data, uint32_t data_length);


#endif // EEPROM_AA32AF_H