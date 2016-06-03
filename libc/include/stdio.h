#ifndef _STDIO_H
#define _STDIO_H

#include <stdarg.h>
#include <stddef.h>

#define EOF -1 //Must be a negative value

char* gets_s(char* buffer, size_t buffer_size);
int printf(const char* restrict format, ...);
int putchar(int c);
int puts(const char* str);

#endif
