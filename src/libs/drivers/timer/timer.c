#include "timer.h"
#include "../../../kernel/IDT_PIC.h"
#include "../../interrupts.h"
#include "../terminal/terminal.h"

extern void asm_timer_handler();

volatile unsigned int timer_ticks = 0;

int init_timer(unsigned int frequancy) {
  unsigned int divisor = 1193182 / frequancy;
  IDT_reg_handler(32, 0x08, 0x8E, asm_timer_handler);
  outb(0x43, 0x36);
  outb(0x40, divisor & 0xFF);
  outb(0x40, (divisor >> 8) & 0xFF);
  return 1;
}

void timer_handler() {
  timer_ticks++;
  print_char(45, 10, timer_ticks);
  end_interrupt();
}
