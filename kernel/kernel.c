#include <norby/colortest.h>
#include <norby/gdt.h>
#include <norby/idt.h>
#include <norby/irq.h>
#include <norby/isrs.h>
#include <norby/kernel.h>
#include <norby/keyboard.h>
#include <norby/panic.h>
#include <norby/version.h>
#include <norby/vga.h>
#include <stdio.h>
#include <string.h>

void kmain() {
	//Install descriptor tables
	install_gdt();
	install_idt();
	install_isrs();
	install_irq();
	install_keyboard();
	asm volatile ("sti");

	//Set up VGA text mode, and print a welcome message
	initialize_screen();
	set_text_colors(VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);
	clear_screen();
	printf("NorbyOS v%s\n", NORBY_VERSION);
	char* buffer = "";
	size_t buffer_size = 100;
	while(1) {
		printf("==> ");
		gets_s(buffer, buffer_size);
		if(strcmp(buffer, "colortest") == 0) {
			colortest();
		}
		else if(strcmp(buffer, "clear") == 0) {
			clear_screen();
		}
		else {
			printf("Unrecognized command: %s\n", buffer);
		}
		memset(buffer, 0, buffer_size);
	}

	//Enter an endless loop. If you disable this, another loop in boot.asm will
	//start, but interrupts will be disabled.
	while (1) {}
}
