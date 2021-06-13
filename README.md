# STM32F0-Kernel
This is a basic kernel for an STM32F091RC microcontroller. No API is used except for the C language itself.

## Purpose
The purpose of this project is to outline a very simple yet functional kernel for a barebones operating system. 
It will have dynamic peripheral handling from user input devices to memory expansion (volatile and nonvolatile).

## Architecture
This microcontroller can be connected to an I2C-EEPROM via I2C port 1, and an SPI-OLED display via SPI port 2. 
More compatibility and diversity will be added and supported over time.


