#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/io.h>
#include <norby/vga.h>

uint8_t make_vga_color(enum vga_color fg, enum vga_color bg) {
  return fg | bg << 4;
}

uint16_t make_vga_entry(char c, uint8_t color) {
  uint16_t c16 = c;
  uint16_t color16 = color;
  return c16 | color16 << 8;
}

size_t vga_row;
size_t vga_column;
uint8_t vga_color;
uint16_t* vga_buffer;

void initialize_screen() {
  vga_row = 0;
  vga_column = 0;
  vga_color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
  vga_buffer = (uint16_t*) 0xB8000;
  clear_screen();
}

void clear_screen() {
  for(int y = 0; y < VGA_HEIGHT; y++) {
    for(int x = 0; x < VGA_WIDTH; x++) {
      put_char_at(' ', x, y);
    }
  }
  vga_row = 0;
  vga_column = 0;
  update_cursor_position();
}

void set_text_colors(enum vga_color fg, enum vga_color bg) {
  vga_color = make_vga_color(fg, bg);
}

void update_cursor_position() {
  int newpos_x = vga_column ;
  int newpos_y = vga_row;
  if(vga_row > VGA_WIDTH) {
    newpos_x = 0;
  }
  set_cursor_position(newpos_x, newpos_y);
}

void set_cursor_position(int x, int y) {
  uint16_t position = y * VGA_WIDTH + x;
  outb(0x3D4, 14);
  outb(0x3D5, position >> 8);
  outb(0x3D4, 15);
  outb(0x3D5, position);
}

void put_char_at(char c, int x, int y) {
  int pos = y * VGA_WIDTH + x;
  vga_buffer[pos] = make_vga_entry(c, vga_color);
}
