#include "math.h"

uint32_t abs(int32_t num)
{
    int mask = num >> sizeof(int32_t) * 8 - 1;
    return (num + mask) ^ mask;
}

int32_t divide(int32_t dividend, int32_t divisor)
{ 
    int32_t sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
 
    dividend = abs(dividend);
    divisor = abs(divisor);
 
    // Initialize the quotient
    int32_t quotient = 0;
    while (dividend >= divisor)
    {
        dividend -= divisor;
        ++quotient;
    }
 
    return sign * quotient;
}

// uint32_t log10(uint32_t num)
// {
//     return (num >= 1000000000) ? 9 : (num >= 100000000) ? 8 : (num >= 10000000) ? 7 : 
//         (num >= 1000000) ? 6 : (num >= 100000) ? 5 : (num >= 10000) ? 4 : 
//         (num >= 1000) ? 3 : (num >= 100) ? 2 : (num >= 10) ? 1 : 0;
// }