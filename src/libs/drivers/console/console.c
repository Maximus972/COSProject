#include "console.h"
#include "../keyboard/keyboard.h"
#include "../terminal/terminal.h"

static char line_buffer[128];
static int line_length = 0;
static int line_ready = 0;

void console_print_prompt() { terminal_write("master$ "); }
void console_init() {
  line_length = 0;
  line_ready = 0;
  console_print_prompt();
}

void console_handle_backspace() {
  if (line_length > 0) {
    line_length--;
    line_buffer[line_length] = '\0';

    terminal_backspace();
  }
}

void console_poll_input() {
  while (keyboard_has_char()) {
    char c = keyboard_get_char();

    if (c == '\b') {
      console_handle_backspace();
      continue;
    }

    if (c == '\n') {
      terminal_putchar('\n');
      line_buffer[line_length] = '\0';
      line_ready = 1;
      line_length = 0;
      return;
    }

    if (!line_ready && line_length < 127) {
      line_buffer[line_length++] = c;
      terminal_putchar(c);
    }
  }
}

int console_has_line() { return line_ready; }

char *console_get_line() {
  line_ready = 0;
  return line_buffer;
}
