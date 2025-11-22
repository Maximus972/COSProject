#ifndef IDT_PIC
#define IDT_PIC

typedef void (*intr_handler)();

void PIC_remap();
void interrup_enabled();
void interrup_disabled();
void IDT_reg_handler(
    unsigned short addr_low_bits,
    unsigned short segm_selector,
    unsigned char nulls,
    unsigned char flags,
    unsigned short addr_high_bits
);
void load_IDT();

#endif