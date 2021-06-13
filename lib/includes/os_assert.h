#ifndef ASSERT_H
#define ASSERT_H

#include "oled_1602a.h"

#define ASSERT(cond, message) \
    if (!(cond)) { \
        oled_clear_display1();  \
        oled_display1(message); \
    } \

#endif // ASSERT_H