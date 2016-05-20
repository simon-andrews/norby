#ifndef NORBY_IRQ_H
#define NORBY_IRQ_H

#include <norby/misc.h>

void install_irq();
void irq_install_handler(int irq, void (*handler)(struct regs* r));
void irq_uninstall_handler(int irq);

#endif
