/* kernel.c */
#include "../libs/drivers/keyboard/keyboard.h"
#include "../libs/drivers/terminal/terminal.h"
#include "../libs/drivers/timer/timer.h"
#include "../libs/interrupts.h"
#include "IDT_PIC.h"
#include "exceptions.h"
#include "gdt.h"

/* Объявляем функцию, которая принимает аргументы от GRUB (пока не используем)
 */
void kmain(void) {
  interrupt_disabled();
  terminal_init();
  terminal_write("Hello ContraOS!\n");
  terminal_write("Terminal init success!\n");
  gdt_init();
  terminal_write("GDB init success!\n");
  init_keyboard();
  terminal_write("Keyboard init success!\n");
  init_timer(100);
  init_exceptions();
  terminal_write("Timer init success!\n");
  load_IDT();
  terminal_write("IDT init success!\n");
  PIC_remap();
  PIC_update_mask(0, 0, 0);
  PIC_update_mask(0, 1, 0);
  // int y = 100;
  // for (int i = 2; i > -2; i = i - 1) {
  //   y = y / i;
  // }
  interrupt_enabled();
  terminal_write("Interrupts enabled!\n");
  terminal_write_with_color("ERROR: error message!", 4);

  for (;;) {
    asm volatile("hlt");

    while (keyboard_has_char()) {
      char c = keyboard_get_char();
      terminal_putchar(c);
    }
  }
  // loading_movement(25, 22, 0x07); //
  // wait(500000000);
  return;
}
