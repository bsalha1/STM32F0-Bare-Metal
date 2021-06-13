#ifndef SPI_H
#define SPI_H

#include "int.h"

struct spi {
    uint32_t cr1;     // Control register 1
    uint32_t cr2;     // Control register 2
    uint32_t sr;      // Status register
    uint32_t dr;      // Data register
    uint32_t crcpr;   // CRC polynomial register
    uint32_t rxcrcr;  // RX CRC register
    uint32_t txcrcr;  // TX CRC register
    uint32_t i2scfgr; // I2S configuration register
    uint32_t i2spr;   // I2S prescaler register
};

#define SPI_1 ((volatile struct spi*)0x40013000)
#define SPI_2 ((volatile struct spi*)0x40003800)

#define SPI_CR1_CPHA     (1 << 0)
#define SPI_CR1_CPOL     (1 << 1)
#define SPI_CR1_MSTR     (1 << 2)
#define SPI_CR1_BR       (0x7 << 3)
#define SPI_CR1_SPE      (1 << 6)
#define SPI_CR1_LSBFIRST (1 << 7)
#define SPI_CR1_SSI      (1 << 8)
#define SPI_CR1_SSM      (1 << 9)
#define SPI_CR1_RXONLY   (1 << 10)
#define SPI_CR1_CRCL     (1 << 11)
#define SPI_CR1_CRCNEXT  (1 << 12)
#define SPI_CR1_CRCEN    (1 << 13)
#define SPI_CR1_BIDIOE   (1 << 14)
#define SPI_CR1_BIDIMODE (1 << 15)

#define SPI_CR2_RXDMAEN (1 << 0)
#define SPI_CR2_TXDMAEN (1 << 1)
#define SPI_CR2_SSOE    (1 << 2)
#define SPI_CR2_NSSP    (1 << 3)
#define SPI_CR2_FRF     (1 << 4)
#define SPI_CR2_ERRIE   (1 << 5)
#define SPI_CR2_RXNEIE  (1 << 6)
#define SPI_CR2_TXNEIE  (1 << 7)
#define SPI_CR2_DS      (0xF << 8)
#define SPI_CR2_FRXTH   (1 << 12)
#define SPI_CR2_LDMA_RX (1 << 13)
#define SPI_CR2_LDMA_TX (1 << 14)

#define SPI_SR_TXE (1 << 1)

enum spi_port {
    SPI_PORT_1 = 0,
    SPI_PORT_2 = 1
};

void enable_spi(enum spi_port port);

#endif // SPI_H