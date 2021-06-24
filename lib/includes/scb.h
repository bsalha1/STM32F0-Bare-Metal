#ifndef SCB_H
#define SCB_H

#include "int.h"

#define SCB_CPUID_REVISION     0xF
#define SCB_CPUID_PARTNO      (0xFFF << 4)
#define SCB_CPUID_CONSTANT    (0xF << 16)
#define SCB_CPUID_VARIANT     (0xF << 20)
#define SCB_CPUID_IMPLEMENTER (0xFF << 24)

struct scb {
    uint32_t cpuid; // CPUID base register
    uint32_t icsr;  // Interrupt control and state register
    uint32_t aircr; // Application interrupt and reset control register
    uint32_t scr;   // System control register
    uint32_t ccr;   // Configuration and control register
    uint32_t shpr2; // System handler priority register 2
    uint32_t shpr3; // System handler priority register 3
};

#define SCB ((volatile struct scb*)0xE000ED00)

/**
 * @brief Returns revision of CPU ex: patch 0
 */
uint8_t cpu_get_revision();

/**
 * @brief Returns part number of CPU ex: Cortex-M0 = 0xC20
 */
uint16_t cpu_get_partno();

/**
 * @brief Returns architecture of CPU ex: ARMv6-M = 0xC
 */
uint8_t cpu_get_arch();

/**
 * @brief Returns variant of CPU ex: revision 0
 */
uint8_t cpu_get_variant();

/**
 * @brief Returns implementer code ex: ARM = 0x41
 */
uint8_t cpu_get_implementer();

#endif // SCB_H