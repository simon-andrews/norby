; main.asm - Barebones x86 Assembly to run an external function
; Works on Linux only. ;)

global _start  ; so the linker knows where the entry point is
extern do_test ; the test itself is defined externally

section .text
_start:
  call do_test ; run the test
  mov ebx, eax ; set return code (0 is success, everything else is failure)
  mov eax, 1   ; set system call number (sys_exit)
  int 0x80     ; call kernel
