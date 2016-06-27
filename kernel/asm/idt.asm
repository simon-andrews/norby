global load_idt
extern idtp
load_idt:
  lidt [idtp]
  ret
