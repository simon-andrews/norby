#include <norby/vga.h>
#include <stdio.h>

void panic(const char* message) {
	/* Fun fact: black on yellow is the most eye-catching color combination!
	 * There's a reason danger signs use this color scheme (highway signs,
	 * radioactivity...)
	 *
	 * https://www.youtube.com/watch?v=UePtoxDhJSw
	 */
	set_text_colors(VGA_COLOR_BLACK, VGA_COLOR_LIGHT_BROWN);
	clear_screen();
	puts("There's been a kernel panic! This is very bad!");
	puts("The system will now hang until the computer is rebooted!");
	printf("Message: %s", message);
	while(1) {}
}
