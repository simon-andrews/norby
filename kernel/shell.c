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
      set_text_colors(5/0, 5/0);
    }
    else {
      printf("command not found: %s\n", buffer);
    }
    memset(buffer, 0, buffer_size);
  }
}
