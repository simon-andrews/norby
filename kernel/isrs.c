#include <norby/idt.h>
#include <norby/misc.h>
#include <norby/panic.h>

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void install_isrs() {
  idt_set_gate(0, (unsigned) isr0, 0x08, 0x8E);
  idt_set_gate(1, (unsigned) isr1, 0x08, 0x8E);
  idt_set_gate(2, (unsigned) isr2, 0x08, 0x8E);
  idt_set_gate(3, (unsigned) isr3, 0x08, 0x8E);
  idt_set_gate(4, (unsigned) isr4, 0x08, 0x8E);
  idt_set_gate(5, (unsigned) isr5, 0x08, 0x8E);
  idt_set_gate(6, (unsigned) isr6, 0x08, 0x8E);
  idt_set_gate(7, (unsigned) isr7, 0x08, 0x8E);
  idt_set_gate(8, (unsigned) isr8, 0x08, 0x8E);
  idt_set_gate(9, (unsigned) isr9, 0x08, 0x8E);
  idt_set_gate(10, (unsigned) isr10, 0x08, 0x8E);
  idt_set_gate(11, (unsigned) isr11, 0x08, 0x8E);
  idt_set_gate(12, (unsigned) isr12, 0x08, 0x8E);
  idt_set_gate(13, (unsigned) isr13, 0x08, 0x8E);
  idt_set_gate(14, (unsigned) isr14, 0x08, 0x8E);
  idt_set_gate(15, (unsigned) isr15, 0x08, 0x8E);
  idt_set_gate(16, (unsigned) isr16, 0x08, 0x8E);
  idt_set_gate(17, (unsigned) isr17, 0x08, 0x8E);
  idt_set_gate(18, (unsigned) isr18, 0x08, 0x8E);
  idt_set_gate(19, (unsigned) isr19, 0x08, 0x8E);
  idt_set_gate(20, (unsigned) isr20, 0x08, 0x8E);
  idt_set_gate(21, (unsigned) isr21, 0x08, 0x8E);
  idt_set_gate(22, (unsigned) isr22, 0x08, 0x8E);
  idt_set_gate(23, (unsigned) isr23, 0x08, 0x8E);
  idt_set_gate(24, (unsigned) isr24, 0x08, 0x8E);
  idt_set_gate(25, (unsigned) isr25, 0x08, 0x8E);
  idt_set_gate(26, (unsigned) isr26, 0x08, 0x8E);
  idt_set_gate(27, (unsigned) isr27, 0x08, 0x8E);
  idt_set_gate(28, (unsigned) isr28, 0x08, 0x8E);
  idt_set_gate(29, (unsigned) isr29, 0x08, 0x8E);
  idt_set_gate(30, (unsigned) isr30, 0x08, 0x8E);
  idt_set_gate(31, (unsigned) isr31, 0x08, 0x8E);
}

//https://en.wikipedia.org/wiki/Interrupt_descriptor_table#Hardware-generated_exceptions
const char* exception_messages[] = {
  /* 0x00 */ "Division By Zero",
  /* 0x01 */ "Debugger",
  /* 0x02 */ "Non-Maskable Interrupt",
  /* 0x03 */ "Breakpoint",
  /* 0x04 */ "Into Detected Overflow",
  /* 0x05 */ "Out of Bounds",
  /* 0x06 */ "Invalid Opcode",
  /* 0x07 */ "Coprocessor Not Available",
  /* 0x08 */ "Double Fault",
  /* 0x09 */ "Coprocessor Segment Overrun",
  /* 0x0A */ "Invalid Task State Segment (TSS)",
  /* 0x0B */ "Segment Not Present",
  /* 0x0C */ "Stack Fault",
  /* 0x0D */ "General Protection Fault",
  /* 0x0E */ "Page Fault",
  /* 0x0F */ "Unknown Interrupt",
  /* 0x10 */ "Math Fault",
  /* 0x11 */ "Alignment Check",
  /* 0x12 */ "Machine Check",
  /* 0x13 */ "SIMD Floating-Point Exception",
  /* 0x14 */ "Virtualization Exception",
  /* 0x15 */ "Control Protection Exception",
  /* 0x16 */ "Reserved (22)",
  /* 0x17 */ "Reserved (23)",
  /* 0x18 */ "Reserved (24)",
  /* 0x19 */ "Reserved (25)",
  /* 0x1A */" Reserved (26)",
  /* 0x1B */ "Reserved (27)",
  /* 0x1C */ "Reserved (28)",
  /* 0x1D */ "Reserved (29)",
  /* 0x1E */ "Security Exception", // http://wiki.osdev.org/Exceptions
  /* 0x1F */ "Reserved (31)",
};

void fault_handler(struct regs* r) {
  if(r->int_no < 32) {
    panic(exception_messages[r->int_no]);
  }
}
