global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

%macro ISR_NOERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERROCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERROCODE  8
ISR_NOERRCODE 9
ISR_ERROCODE  10
ISR_ERROCODE  11
ISR_ERROCODE  12
ISR_ERROCODE  13
ISR_ERROCODE  14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

extern fault_handler

isr_common_stub:
  pusha
  push ds
  push es
  push fs
  push gs
  mov ax, 0x10
  mov ds, ax
  mov es, ax
  mov fs, ax
  mov gs, ax
  mov eax, esp
  push eax
  mov eax, fault_handler
  call eax
  pop eax
  pop gs
  pop fs
  pop es
  pop ds
  popa
  add esp, 8
  iret
;  pusha        ; push edi, esi, ebp, esp, ebx, edx, ecx, eax to the stack
;  mov ax, ds   ; lower 16 bits of eax = data segment descriptor
;  push eax     ; save data segment descriptor
;
;  mov ax, 0x10 ; load the kernel data segment descriptor
;  mov ds, ax
;  mov es, ax
;  mov fs, ax
;  mov gs, ax
;
;  call fault_handler
;
;  pop eax      ; reload the original data segment descriptor
;  mov ds, ax
;  mov es, ax
;  mov fs, ax
;  mov gs, ax
;
;  popa         ; pop edi...eax from the stack
;  add esp, 8   ; clean up pushed error code and pushed ISR number
;  iret         ; pop cs, eip, eflags, ss, and esp
