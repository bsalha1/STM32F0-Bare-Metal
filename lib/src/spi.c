#include "spi.h"
#include "rcc.h"

void enable_spi(enum spi_port port)
{
    if(port == SPI_PORT_1)
    {
        RCC->apb2enr |= 1 << 12;
    }
    else if(port == SPI_PORT_2)
    {
        RCC->apb1enr |= 1 << 14;
    }
    else
    {
        // TODO: assert
    }
}
