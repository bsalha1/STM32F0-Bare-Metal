#ifndef _OS_ASSERT_H
#define _OS_ASSERT_H

#include "oled_1602a.h"

#define OS_ASSERT(cond, message) \
    if (!(cond)) { \
        oled_clear_display1();  \
        oled_display1(message); \
    } \

#endif // _OS_ASSERT_H