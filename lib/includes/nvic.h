#ifndef _NVIC_H_
#define _NVIC_H_

#define NVIC 0xE000E100
#define NVIC_ISER ((volatile uint32_t *) NVIC + 0x000)
#define NVIC_ICER ((volatile uint32_t *) NVIC + 0x080) 
#define NVIC_ISPR ((volatile uint32_t *) NVIC + 0x100)
#define NVIC_ICPR ((volatile uint32_t *) NVIC + 0x180)

#define NVIC2 0xE000EF00
#define NVIC2_ISER ((volatile uint32_t *) NVIC2 + 0x000)
#define NVIC2_ICER ((volatile uint32_t *) NVIC2 + 0x080) 
#define NVIC2_ISPR ((volatile uint32_t *) NVIC2 + 0x100)
#define NVIC2_ICPR ((volatile uint32_t *) NVIC2 + 0x180)

#endif // _NVIC_H_