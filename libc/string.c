#include <stddef.h>
#include <stdint.h>
#include <string.h>

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

int strcmp(const char* str1, const char* str2) {
  if(str1 == str2) {
    return 0;
  }
  if((str1[0] == '\0' || str2[0] == '\0') && (str1[0] != str2[0])) {
    return -1; //It's what GLibC does, I think...
  }
  size_t longest_len = (strlen(str1) < strlen(str2)) ? strlen(str1) : strlen(str2);
  for(unsigned int i = 0; i < longest_len; i++) {
    if(!(str1[i] == str2[i])) {
      return (int) str1[i] - str2[i];
    }
  }
  return 0;
}

size_t strlen(const char* str) {
  size_t length = 0;
  while(str[length] != 0) {
    length++;
  }
  return length;
}
