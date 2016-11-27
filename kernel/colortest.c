#include <norby/vga.h>
#include <stdio.h>

void colortest() {
  uint8_t old_color = get_current_text_color();
  for(unsigned int background = 0; background <= 15; background++) {
    for(unsigned int foreground = 0; foreground <= 15; foreground++) {
      set_text_colors(foreground, background);
      putchar('*');
      set_text_color(old_color);
    }
    putchar('\n');
  }
  set_text_color(old_color);
}
