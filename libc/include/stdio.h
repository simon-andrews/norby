#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>

#define EOF -1 //Must be a negative value

int printf(const char* restrict format, ...);
int putchar(int c);
int puts(const char* str);

#endif
