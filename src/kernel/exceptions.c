#include "exceptions.h"
#include "../libs/drivers/terminal/terminal.h"
#include "IDT_PIC.h"

extern void isr0();
extern void isr6();
extern void isr13();
extern void isr14();

char *const INT_0_MSG = "Divide Error\n";
char *const INT_6_MSG = "Invalid Opcode\n";
char *const INT_13_MSG = "General Protection Fault\n";
char *const INT_14_MSG = "Page Fault\n";

void init_exceptions() {
  IDT_reg_handler(0, 0x08, 0x8E, isr0);
  IDT_reg_handler(6, 0x08, 0x8E, isr6);
  IDT_reg_handler(13, 0x08, 0x8E, isr13);
  IDT_reg_handler(14, 0x08, 0x8E, isr14);
}

void exception_handler(int vector) {
  terminal_write("CPU exception: ");

  if (vector == 0)
    terminal_write(INT_0_MSG);
  if (vector == 6)
    terminal_write(INT_6_MSG);
  if (vector == 13)
    terminal_write(INT_13_MSG);
  if (vector == 14)
    terminal_write(INT_14_MSG);
}
