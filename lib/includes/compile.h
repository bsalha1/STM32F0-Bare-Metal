#ifndef _COMPILE_H
#define _COMPILE_H

#define __attribute_section__(sec) __attribute__((section(sec)))

#define __WEAK__ __attribute__((weak))
#define __VECTOR__ __attribute_section__(".vectors")

#endif // _COMPILE_H