#include <norby/irq.h>
#include <stdbool.h>
#include <stdio.h>
#include <sys/io.h>

char last_pressed;
bool new_key_availible;

const char set1_scan_codes[] = {
  0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  '-', '=',
  '\b',	// Backspace
  '\t',	// Tab
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
  '\n', // Enter key
  0, //Control key
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
  '\'', '`',   0, // Left shift
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
  0, // Right shift
  '*',
  0, // Alt
  ' ', // Space bar
  0,	// Caps lock
  0,	// 59 - F1 key ... >
  0,   0,   0,   0,   0,   0,   0,   0,
  0,	// < ... F10
  0,	// 69 - Num lock*/
  0,	// Scroll Lock
  0,	// Home key
  0,	// Up Arrow
  0,	// Page Up
  '-',
  0,	// Left Arrow
  0,
  0,	// Right Arrow
  '+',
  0,	// 79 - End key*/
  0,	// Down Arrow
  0,	// Page Down
  0,	// Insert Key
  0,	// Delete Key
  0,   0,   0,
  0,	// F11 Key
  0,	// F12 Key
  0,	// All other keys are undefined
};

char get_latest_char() {
  new_key_availible = false;
  return last_pressed;
}

bool new_key_is_availible() {
  return new_key_availible;
}

//void keyboard_handler(struct regs* r) {
void keyboard_handler() {
  unsigned char scancode = inb(0x60);
  if(scancode & 0x80) {
    //pass, for now
  }
  else if(set1_scan_codes[scancode] == 0) {
    //pass
  }
  else {
    last_pressed = set1_scan_codes[scancode];
    new_key_availible = true;
  }
}

void install_keyboard() {
  new_key_availible = false;
  irq_install_handler(1, keyboard_handler);
}
