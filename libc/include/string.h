#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* destination, int chr, size_t count);
size_t strlen(const char* str);

#endif
