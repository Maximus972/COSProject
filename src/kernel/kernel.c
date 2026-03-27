/* kernel.c */
#include "../libs/drivers/keyboard.h"
#include "../libs/drivers/terminal/terminal.h"
#include "../libs/interrupts.h"
#include "IDT_PIC.h"
#include "gdt.h"

int x_coordinate = 0;
int y_coordinate = 0;

// TODO: Функция ожидания, необходимо ее переделать
void wait(int count_max) {
  int count = 0;
  while (count <= count_max) {
    asm volatile("" :::);
    count = count + 1;
  }
}

/* Объявляем функцию, которая принимает аргументы от GRUB (пока не используем)
 */
void kmain(void) {
  interrupt_disabled();
  print_char(50, 22, 'C');
  in_out_wait();
  gdt_init(); // * Инициализация GDT
  print_char(30, 11, 'B');
  init_keyboard();
  load_IDT();
  PIC_remap();
  PIC_update_mask(0, 1, 0);
  wait(500000000);

  interrupt_enabled();
  wait(500000000);

  // for (;;) {
  //   asm volatile("hlt");
  // }
  loading_movement(25, 22, 0x07); //
  // wait(500000000);
  return;
}
