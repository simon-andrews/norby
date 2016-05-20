#ifndef NORBY_IDT_H
#define NORBY_IDT_H

#include <stdint.h>

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void install_idt();

#endif
