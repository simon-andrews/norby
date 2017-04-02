#ifndef NORBY_MEMORY_H
#define NORBY_MEMORY_H

#include <stdint.h>

#define VGA_TEXT_MODE_BUFFER (0xB8000)

#define E820_SIGNATURE (0x534D4150)

typedef struct {
  uint32_t base_lo;
  uint32_t base_hi;
  uint32_t length_lo;
  uint32_t length_hi;
  uint32_t type;
  uint32_t acpi;
} __attribute__((packed)) memory_map_entry_t;

int __attribute__((noinline)) __attribute__((regparm(3))) detect_memory(memory_map_entry_t* buffer, int maxentries);
int get_base_memory_size();

#endif
