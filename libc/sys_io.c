#include <stdint.h>

void outb(uint16_t port, uint8_t value) {
  asm volatile ("outb %1, %0" : : "dN" (port), "a" (value));
}

unsigned char inb(uint16_t port) {
  unsigned char ret;
  asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

void outl(uint16_t port, uint32_t value) {
  asm volatile ("outl %1, %0" : : "dN" (port), "a" (value));
}

uint32_t inl(uint16_t port) {
  uint32_t ret;
  asm volatile ("inl %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}
