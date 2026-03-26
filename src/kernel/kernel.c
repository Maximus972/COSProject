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

  print_char(50, 22, 'C');

  wait(500000000);

  in_out_wait();

  gdt_init(); // * Инициализация GDT

  wait(500000000);

  print_char(30, 11, 'B');

  wait(500000000);

  PIC_remap();

  load_IDT();

  init_keyboard();

  loading_movement(25, 25, 0x07); //

  return;
}
