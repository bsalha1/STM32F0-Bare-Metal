#ifndef _COMPILE_H
#define _COMPILE_H

#define __attribute_section__(sec) __attribute__((section(sec)))

#define VECTOR_CODE __attribute_section__(".vectors")

#endif // _COMPILE_H