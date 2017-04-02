#include <norby/colortest.h>
#include <norby/gdt.h>
#include <norby/idt.h>
#include <norby/irq.h>
#include <norby/isrs.h>
#include <norby/kernel.h>
#include <norby/keyboard.h>
#include <norby/memory.h>
#include <norby/panic.h>
#include <norby/shell.h>
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

	//Figure out how much memory we have
	int entry_count = get_base_memory_size();
	if(entry_count < 0) {
		printf("signature verification failed when attempting to detect memory\n");
	}
	else {
		printf("# of entries available: %d\n", entry_count);
	}
	printf("return value for get_base_memory_size(): %d\n", entry_count);
	start_shell();

	//Enter an endless loop. If you disable this, another loop in boot.asm will
	//start, but interrupts will be disabled.
	while (1) {}
}
