#include "log.h"

volatile char log_text[LOG_SIZE] = {0};
static int log_ptr;

void log_message(char* message)
{
    for(int i = 0; log_ptr < LOG_SIZE; log_ptr++, i++)
    {
        log_text[log_ptr] = message[i];
    }
}

int log_get_current_length()
{
    return log_ptr;
}

void log_copy(char* dest, int size)
{
    if(size >= LOG_SIZE)
    {
        // TODO: assert
        return;
    }

    for(int i = 0; i < size; i++)
    {
        dest[i] = log_text[i];
    }
}

