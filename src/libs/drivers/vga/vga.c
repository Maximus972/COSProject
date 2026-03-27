#include "vga.h"

static uint_8 *const VGA_MEMORY = (uint_8 *)0xB8000;

uint_8 vga_make_color(uint_8 fg, uint_8 bg) { return fg | (bg << 4); }

uint_16 vga_make_entry(char c, uint_8 color) {
  return (uint_16)c | ((uint_16)color << 8);
}

void vga_put_entry_at(char c, uint_8 color, int x, int y) {
  int index = y * VGA_WIDTH + x;
  VGA_MEMORY[index] = vga_make_entry(c, color);
}

void vga_clear(uint_8 color) {
  uint_16 empty = vga_make_entry(' ', color);
  for (int y = 0; y < VGA_HEIGHT; y++) {
    for (int x = 0; x < VGA_WIDTH; x++) {
      VGA_MEMORY[y * VGA_WIDTH + x] = empty;
    }
  }
}
