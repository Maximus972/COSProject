#ifndef KEYBOARD_DRIVER
#define KEYBOARD_DRIVER

int init_keyboard();
void keyboard_handler();

int keyboard_has_char();
char keyboard_get_char();

#endif
