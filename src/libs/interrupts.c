#include "interrupts.h"

void interrupt_enabled() { asm("sti"); }
void interrupt_disabled() { asm("cli"); }
void end_interrupt() { outb(0x20, 0x20); }
