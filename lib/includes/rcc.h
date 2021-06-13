#ifndef RCC_H
#define RCC_H

#include "int.h"

struct rcc {
    uint32_t cr;       // Clock control register
    uint32_t cfgr;     // Clock configuration register
    uint32_t cir;      // Clock interrupt register
    uint32_t apb2rstr; // APB peripheral reset register 2
    uint32_t apb1rstr; // APB peripheral reset register 1
    uint32_t ahbenr;   // AHB peripheral clock enable register
    uint32_t apb2enr;  // APB peripheral clock enable register 2
    uint32_t apb1enr;  // APB peripheral clock enable register 1
    uint32_t bdcr;     // RTC domain control register
    uint32_t csr;      // Control/status register
    uint32_t ahbrstr;  // AHB peripheral reset register
    uint32_t cfgr2;    // Clock configuration register 2
    uint32_t cfgr3;    // Clock configuration register 3
    uint32_t cr2;      // Clock control register 2
};

#define RCC ((volatile struct rcc*)0x40021000)

#endif // RCC_H