#ifndef CONSOLE_H
#define CONSOLE_H

void console_init();
void console_poll_input();

int console_has_line();
char *console_get_line();
void console_print_prompt();

#endif
