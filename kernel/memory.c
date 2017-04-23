#include <norby/cmos.h>
#include <norby/memory.h>
#include <stdint.h>
#include <sys/io.h>

int __attribute__((noinline)) __attribute__((regparm(3))) detect_memory(memory_map_entry_t* buffer, int maxentries) {
  uint32_t contID = 0;
  int entries = 0, signature, bytes;

  do {
    //printf("SMAP entry buffer located at memory address: %d\n", buffer);
    asm volatile ("int $0x15"
      : "=a"(signature), "=c"(bytes), "=b"(contID)
      : "a"(0xE820), "b"(contID), "c"(24), "d"(E820_SIGNATURE), "D"(buffer));

    if(signature != E820_SIGNATURE) {
      printf("signature: %d\n", signature);
      printf("bytes: %d\n", bytes);
      printf("contID: %d\n", contID);
      return -1;
    }
    if(bytes > 20 && (buffer->acpi & 0x0001) == 0) {
      //printf("ignoring");
      // ignore this entry
    }
    else {
      //printf("incrementing");
      buffer++;
      entries++;
    }
  } while(contID != 0 && entries < maxentries);
  //printf("returning");
  return entries;
}

int get_base_memory_size() {
/*  uint8_t mem_hi, mem_lo;
  uint16_t total;

  outb(CMOS_IO_PORT_IN, 0x30);
  mem_lo = inb(CMOS_IO_PORT_OUT);
  outb(CMOS_IO_PORT_IN, 0x31);
  mem_hi = inb(CMOS_IO_PORT_OUT);
  total = mem_lo | mem_hi << 8;

  printf("lo: %d, hi: %d\n", mem_lo, mem_hi);
  return total;
*/

  memory_map_entry_t* mmap = (memory_map_entry_t*) 0x1000;
  const int mmap_size = 0x2000;

  int entry_count = detect_memory(mmap, mmap_size / sizeof(memory_map_entry_t));
  return entry_count;
}
