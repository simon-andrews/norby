#include <norby/colortest.h>
#include <norby/shell.h>
#include <norby/vga.h>
#include <stdio.h>
#include <string.h>

void start_shell() {
  size_t buffer_size = 100;
  char* fixed_buffer[buffer_size];
  while(1) {
    char* buffer = fixed_buffer;
    printf("==> ");
    gets_s(buffer, buffer_size);
    if(strcmp(buffer, "colortest") == 0) {
      colortest();
    }
    else if(strcmp(buffer, "clear") == 0) {
      clear_screen();
    }
    else if(strcmp(buffer, "crash") == 0) {
      /*
       * Causes a division by zero exception to occur, leading to a panic.
       * pragma stuff is to disable division by zero warnings.
       */
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wdiv-by-zero"
      set_text_colors(5/0, 5/0);
      #pragma GCC diagnostic pop
    }
    else if(strcmp(buffer, "dumpgenregs") == 0) {
      int eax, ebx, ecx, edx;
      asm volatile("nop" : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx));
      printf("eax: %d\nebx: %d\necx: %d\nedx: %d\n", eax, ebx, ecx, edx);
    }
    else if(strcmp(buffer, "dmem") == 0)  {
      printf("%d\n", get_base_memory_size());
    }
    else {
      printf("command not found: %s\n", buffer);
    }
    memset(buffer, 0, buffer_size);
  }
}
