#ifndef VGA_DRIVER

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

typedef unsigned char uint_8;
typedef unsigned short uint_16;

enum vga_color {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15
};

uint_8 vga_make_color(uint_8 fg, uint_8 bg);
uint_16 vga_make_entry(char c, uint_8 color);

// TODO: Здесь же можно просто добавить вместо c и color сразу готовый uint_16
// параметр, готовый
void vga_put_entry_at(char c, uint_8 color, int x, int y);
void vga_clear(uint_8 color);
#endif
