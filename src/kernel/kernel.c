/* kernel.c */
#include "boot/multiboot.h"
#include "kernel/IDT_PIC.h"
#include "kernel/exceptions.h"
#include "kernel/gdt.h"
#include "libs/drivers/keyboard/keyboard.h"
#include "libs/drivers/shell/shell.h"
#include "libs/drivers/terminal/terminal.h"
#include "libs/drivers/timer/timer.h"
#include "libs/interrupts/interrupts.h"
#include "libs/libc/string.h"
#include "libs/util/buffer.h"

static unsigned int MAGIC_NUMBER = 0x2BADB002;

/* Объявляем функцию, которая принимает аргументы от GRUB (пока не используем)
 */
void kmain(unsigned int magic_number, boot *boot_struct) {
  interrupt_disabled();
  terminal_init();
  char storage[64];
  Buffer buffer;
  buffer_init(&buffer, storage, 64);

  itoa(magic_number, &buffer, 16); // магия в шестнадцатеричном виде
  terminal_write("magic = 0x");
  terminal_write(buffer.data);
  terminal_write("\n");
  if (boot_struct->flags & 1) {
    terminal_write("mem_lower|mem_upper correct value GRUB!\n");
    char storage2[64];
    Buffer buffer2;
    buffer_init(&buffer2, storage2, 64);
    itoa(boot_struct->mem_lower, &buffer2, 16);
    terminal_write("mem_lower: ");
    terminal_write(buffer2.data);
    terminal_write("\n");
    itoa(boot_struct->mem_upper, &buffer2, 16);
    terminal_write("mem_upper: ");
    terminal_write(buffer2.data);
    terminal_write("\n");
  } else {
    terminal_write("mem_lower|mem_upper uncorrect GRUB!\n");
  }
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
