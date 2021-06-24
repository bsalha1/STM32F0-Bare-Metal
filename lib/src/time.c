#include "time.h"
#include "int.h"

static volatile uint64_t millis_since_reset;

void time_init()
{
    millis_since_reset = 0;
}

void small_sleep()
{
    for(int i = 0; i < 5000; i++);
}

void time_increment_millis()
{
    millis_since_reset++;
}

uint64_t time_get_millis_since_reset()
{
    return millis_since_reset;
}