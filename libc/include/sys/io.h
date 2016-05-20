#ifndef _SYS_IO_H
#define _SYS_IO_H

#include <stdint.h>

unsigned char inb(uint16_t port);
void outb(uint16_t port, uint8_t value);

#endif
