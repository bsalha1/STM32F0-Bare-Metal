#include "scb.h"

uint8_t cpu_get_revision()
{
    return SCB->cpuid & SCB_CPUID_REVISION;
}

uint16_t cpu_get_partno()
{
    return (SCB->cpuid & SCB_CPUID_PARTNO) >> 4;
}

uint8_t cpu_get_arch()
{
    return (SCB->cpuid & SCB_CPUID_CONSTANT) >> 16;
}

uint8_t cpu_get_variant()
{
    return (SCB->cpuid & SCB_CPUID_VARIANT) >> 20;
}

uint8_t cpu_get_implementer()
{
    return (SCB->cpuid & SCB_CPUID_IMPLEMENTER) >> 24;
}