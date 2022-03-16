#include "log.h"
#include  <stdlib.h>
#include  <stdio.h>
#include  <stdarg.h>
#pragma warning (disable:4700)

void simple_logger(const char* fmt, ...)
{

    printf("[Simple Log] ");
    va_list args;
    va_start(args, fmt);

    vfprintf(stdout, fmt, args);

    va_end(args);
}
