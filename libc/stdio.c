#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <norby/vga.h>

int printf(const char* restrict format, ...) {
  va_list args;
  va_start(args, format);
  int chars_written = 0;
  for(unsigned int i = 0; i < strlen(format); i++) {
    if(format[i] == '%') {
      chars_written++;
      const char* str; //variables can't be declared in switch statements, so this is here just in case
      //TODO: Implement all the other things (%d, %g...)
      switch(format[i + 1]) {
        case '%':
          putchar('%');
          break;
        case 'c':
          putchar((char) va_arg(args, int));
          break;
        case 's':
          str = va_arg(args, const char*);
          for(unsigned int j = 0; j < strlen(str); j++) {
            putchar(str[j]);
          }
          break;
        default:
          putchar('%'); // I dunno
      }
      i++;
    }
    else {
      chars_written++;
      putchar(format[i]);
    }
  }
  return chars_written;
}

int putchar(int c) {
  if(c == '\n') {
    vga_row++;
    vga_column = 0;
  } else {
    put_char_at(c, vga_column, vga_row);
    vga_column++;
  }
  update_cursor_position();
  return c;
}

int puts(const char* str) {
  for(unsigned int i = 0; i < strlen(str); i++) {
    putchar(str[i]);
  }
  putchar('\n');
  return 1; //returns a positive value on a success
}
