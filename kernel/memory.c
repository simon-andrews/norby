#include <norby/cmos.h>
#include <norby/memory.h>
#include <norby/panic.h>
#include <stdint.h>
#include <sys/io.h>

#define E820_SIGNATURE (0x534D4150)
#define MAX_ENTRIES (512)

typedef struct {
  uint32_t base_lo;
  uint32_t base_hi;
  uint32_t length_lo;
  uint32_t length_hi;
  uint32_t type;
  uint32_t acpi;
} __attribute__((packed)) memory_map_entry_t;

int get_base_memory_size() {
  uint8_t mem_hi, mem_lo;
  uint16_t total;

  outb(CMOS_IO_PORT_IN, 0x30);
  mem_lo = inb(CMOS_IO_PORT_OUT);
  outb(CMOS_IO_PORT_IN, 0x31);
  mem_hi = inb(CMOS_IO_PORT_OUT);
  total = mem_lo | mem_hi << 8;

  printf("lo: %d, hi: %d\n", mem_lo, mem_hi);
  return total;
}
