#include <vga/vga.h>
#include <essentials.h>
#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

size_t vga_index_x = 0;
size_t vga_index_y = 0;

uint16_t *terminal_buffer = (unsigned short *) 0xB8000;

uint8_t vga_init_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

uint16_t vga_entry_set(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void vga_newline_check() {
	if (vga_index_x > VGA_WIDTH) {
		vga_index_x = 0;
		vga_index_y++;
	}
}

void kputcharn(char ch, size_t i) {
	terminal_buffer[i] = vga_entry_set(ch, vga_init_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}

void kputchar(char ch) {
	kputcharn(ch, vga_index_y * VGA_WIDTH + vga_index_x);
	vga_index_x++;
	vga_newline_check();
}

void kputs(char *str) {
    for (size_t i = 0; i < strlen(str); i++) {
		kputchar(str[i]);
    }
}

void kputsln(char *str) {
	kputs(str);
	vga_index_x = 0;
	vga_index_y++;
}

void kpcls() {
	for (size_t i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++)
		terminal_buffer[i] = vga_entry_set(' ', vga_init_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK));
}