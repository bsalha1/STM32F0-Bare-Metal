#ifndef TIME_H
#define TIME_H

#include "int.h"

/**
 * @brief Initializes time to the starting point
 **/
void time_init();


void small_sleep();


/**
 * @brief Increments the internal system time
 **/
void time_increment_millis();


/**
 * @brief Gets the internal system time
 * @return Internal system time
 **/
uint64_t time_get_millis_since_reset();

#endif // TIME_H