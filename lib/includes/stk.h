#ifndef STK_H_
#define STK_H_

#include "int.h"

#define STK_CSR_ENABLE (1)
#define STK_CSR_TICKINT (1 << 1)
#define STK_CSR_CLKSOURCE (1 << 2)
#define STK_CSR_COUNTFLAG (1 << 16)

#define STK_RVR_RELOAD (0xFFFFFF)

#define STK_CVR_CURRENT (0xFFFFFF)

#define STK ((volatile struct stk*) 0xE000E010)

struct stk {
    uint32_t csr;
    uint32_t rvr;
    uint32_t cvr;
    uint32_t calib;
};

/**
 * @brief Enables SysTick interrupt every period_ms milliseconds
 * @param period_ms The period of the SysTick interrupt in milliseconds
 **/
void enable_stk(uint32_t period_ms);

#endif // STK_H_