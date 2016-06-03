#ifndef _STRING_H
#define _STRING_H

#include <stddef.h>

void* memcpy(void* dest, const void* src, size_t n);
void* memset(void* destination, int chr, size_t count);
int strcmp(const char* str1, const char* str2);
size_t strlen(const char* str);

#endif
