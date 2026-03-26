#include "../../kernel/IDT_PIC.h"
#include "terminal/terminal.h"

extern void asm_keyboard_handler();

void keyboard_handler() { print_char(50, 22, 'P'); }

int init_keyboard() {
  // TODO: Тут временно заменил значение поля flags на 0x8E. Ранее было значение
  // 0x08 | 0x0E
  IDT_reg_handler(33, 0x08, 0x8E, asm_keyboard_handler);

  return 1;
}
