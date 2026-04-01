#include "terminal.h"
#include "../vga/vga.h"

static int terminal_row;
static int terminal_column;
static uint_8 terminal_color;

enum string_color {
  DEFAULT_COLOR = VGA_COLOR_GREEN,
  ERROR_COLOR = VGA_COLOR_RED,
  WARN_COLOR = VGA_COLOR_CYAN
};

static void terminal_newline() {
  terminal_column = 0;
  terminal_row++;
  if (terminal_row >= VGA_HEIGHT) {
    terminal_row = 0;
  }
}

void terminal_init() {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_make_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK);
  vga_clear(terminal_color);
}

void terminal_set_color(unsigned char color) { terminal_color = color; }

void terminal_write_at(int x, int y, char c) {
  vga_put_entry_at(c, terminal_color, x, y);
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_newline();
    return;
  }

  vga_put_entry_at(c, terminal_color, terminal_column, terminal_row);
  terminal_column++;

  if (terminal_column >= VGA_WIDTH) {
    terminal_newline();
  }
}

void terminal_write(const char *str) {
  int i = 0;
  while (str[i] != '\0') {
    terminal_putchar(str[i]);
    i++;
  }
}

void terminal_write_with_color(const char *str, unsigned char string_color) {
  int i = 0;
  while (str[i] != '\0') {
    if (str[i] == '\n') {
      terminal_newline();
      return;
    }

    vga_put_entry_at(str[i], string_color, terminal_column, terminal_row);
    terminal_column++;

    if (terminal_column >= VGA_WIDTH) {
      terminal_newline();
    }
    i++;
  }
}

void terminal_backspace() {
  if (terminal_column == 0) {
    return;
  }

  terminal_column--;
  vga_put_entry_at(' ', terminal_color, terminal_column, terminal_row);
}

void terminal_clear() {
  vga_clear(terminal_color);
  terminal_row = 0;
  terminal_column = 0;
}
