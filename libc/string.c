#include <stddef.h>
#include <stdint.h>

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
