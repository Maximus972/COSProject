#ifndef TERMINAL_DRIVER_H
#define TERMINAL_DRIVER_H

void terminal_init();
void terminal_set_color(unsigned char color);
void terminal_putchar(char c);
void terminal_write(const char *str);
void terminal_write_with_color(const char *str, unsigned char string_color);
void terminal_write_at(int x, int y, char c);
void terminal_clear();

#endif
