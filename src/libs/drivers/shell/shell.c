#include "shell.h"
#include "../console/console.h"
#include "../terminal/terminal.h"

static int string_equals(const char *a, const char *b) {
  int i = 0;
  while (a[i] != '\0' && b[i] != '\0') {
    if (a[i] != b[i]) {
      return 0;
    }
    i++;
  }
  return a[i] == b[i];
}

void shell_init() { console_init(); }

void shell_poll() {
  console_poll_input();

  if (console_has_line()) {
    char *line = console_get_line();

    if (string_equals(line, "help")) {
      terminal_write("God help you!");
    } else if (string_equals(line, "clear")) {
      terminal_clear();
    } else {
      terminal_write("Unknown Command!");
    }

    console_print_prompt();
  }
}
