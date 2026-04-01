#include "../../../kernel/IDT_PIC.h"
#include "../../interrupts.h"

extern void asm_keyboard_handler();

static volatile char keyboard_buffer[128];
static volatile int keyboard_read_index = 0;
static volatile int keyboard_write_index = 0;
unsigned char ascii[] = {0,    27,  '1', '2',  '3',  '4',  '5', '6', '7',  '8',
                         '9',  '0', '-', '=',  '\b', '\t', 'q', 'w', 'e',  'r',
                         't',  'y', 'u', 'i',  'o',  'p',  '[', ']', '\n', 0,
                         'a',  's', 'd', 'f',  'g',  'h',  'j', 'k', 'l',  ';',
                         '\'', '`', 0,   '\\', 'z',  'x',  'c', 'v', 'b',  'n',
                         'm',  ',', '.', '/',  0,    '*',  0,   ' '};

static char scancode_to_ascii(unsigned char scancode) {
  if (scancode > 58)
    return 0;
  return ascii[scancode];
}

static void keyboard_buffer_put(char c) {
  int next = (keyboard_write_index + 1) % 128;
  if (next != keyboard_read_index) {
    keyboard_buffer[keyboard_write_index] = c;
    keyboard_write_index = next;
  }
}

int keyboard_has_char() { return keyboard_read_index != keyboard_write_index; }

char keyboard_get_char() {
  if (keyboard_read_index == keyboard_write_index) {
    return 0;
  }

  char c = keyboard_buffer[keyboard_read_index];
  keyboard_read_index = (keyboard_read_index + 1) % 128;
  return c;
}

void keyboard_handler() {
  unsigned char scancode = inb(0x60);
  if ((scancode & 0x80) == 0) {
    char c = scancode_to_ascii(scancode);
    if (c != 0) {
      keyboard_buffer_put(c);
    }
  }
  end_interrupt();
}

int init_keyboard() {
  // TODO: Тут временно заменил значение поля flags на 0x8E. Ранее было значение
  // 0x08 | 0x0E
  IDT_reg_handler(33, 0x08, 0x8E, asm_keyboard_handler);

  return 1;
}
