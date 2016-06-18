#include <stdint.h>
#include <string.h>
#include <norby/idt.h>

struct idt_entry {
  uint16_t base_lo;
  uint16_t sel;
  uint8_t always0;
  uint8_t flags;
  uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

idt_entry_t idt[256];
idt_ptr_t idtp;

extern void load_idt();

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].always0 = 0;
  idt[num].flags = flags;
}

void install_idt() {
  idtp.limit = (sizeof (idt_entry_t) * 256) - 1;
  idtp.base = (uint32_t) &idt;
  memset(&idt, 0, sizeof(idt_entry_t) * 256);
  load_idt();
}
