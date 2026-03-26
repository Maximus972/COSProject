#ifndef IDT_PIC
#define IDT_PIC

typedef void (*intr_handler)();

void PIC_remap();
void interrupt_enabled();
void interrupt_disabled();
void IDT_reg_handler(int number, unsigned short segm_sel, unsigned short flags,
                     intr_handler handler);
void PIC_update_mask(unsigned char ms_sl, unsigned char bit,
                     unsigned char value);
void PIC_set_mask(unsigned char master, unsigned char slave);
void load_IDT();

#endif
