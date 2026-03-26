#include "../../kernel/IDT_PIC.h"
#include "../interrupts.h"
#include "terminal/terminal.h"

extern void asm_keyboard_handler();

void keyboard_handler() { print_char(50, 22, 'P'); }

int init_keyboard() {
  interrupt_disabled(); // TODO: Здесь не должно быть отключения прерываний,
                        // внизу включения, потому что включение/выключение
                        // прерываний должно происходить глобально
  PIC_update_mask(0, 1, 0);
  IDT_reg_handler(33, 0x08, 0x08 | 0x0E, asm_keyboard_handler);
  interrupt_enabled();

  return 1;
}
