#include "interrupts.h"

void interrupt_enabled() { asm("sti"); }
void interrupt_disabled() { asm("cli"); }
