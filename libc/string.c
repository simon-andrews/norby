#include <stddef.h>
#include <stdint.h>

void* memcpy(void* dest, const void* src, size_t n) {
  uint8_t* u8_dest = (uint8_t*) dest;
  const uint8_t* u8_src = (const uint8_t*) src;
  for(unsigned int i = 0; i < n; i++) {
    u8_dest[i] = u8_src[i];
  }
  return u8_dest;
}

void* memset(void* destination, int chr, size_t count) {
  uint8_t* buffer = (uint8_t*) destination;
  for(unsigned int i = 0; i < count; i++) {
    buffer[i] = chr;
  }
  return destination;
}

size_t strlen(const char* str) {
  size_t length = 0;
  while(str[length] != 0) {
    length++;
  }
  return length;
}
