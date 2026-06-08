/* kernel.c */
#include "kernel/IDT_PIC.h"
#include "kernel/exceptions.h"
#include "kernel/gdt.h"
#include "libs/drivers/keyboard/keyboard.h"
#include "libs/drivers/shell/shell.h"
#include "libs/drivers/terminal/terminal.h"
#include "libs/drivers/timer/timer.h"
#include "libs/interrupts.h"

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
  interrupt_enabled();
  terminal_write("Interrupts enabled!\n");
  shell_init();
  for (;;) {
    asm volatile("hlt");
    shell_poll();
  }
  return;
}
