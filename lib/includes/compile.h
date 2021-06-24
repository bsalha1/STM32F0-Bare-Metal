#ifndef COMPILE_H
#define COMPILE_H

#define STACK_SIZE 256

#define __attribute_section__(sec) __attribute__((section(sec)))

#define __weak__ __attribute__((weak))
#define __interrupt__ __attribute__((interrupt))
#define __vector__ __attribute_section__(".vectors")

#endif // COMPILE_H