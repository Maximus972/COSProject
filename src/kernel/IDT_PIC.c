#include "IDT_PIC.h"
#include "../libs/interrupts.h"

struct IDT_DESCRIPTOR {
  unsigned short addr_low_bits;
  unsigned short segm_selector;
  unsigned char nulls;
  unsigned char flags;
  unsigned short addr_high_bits;
} __attribute__((packed));

struct IDT_BASE {
  unsigned short limit;
  unsigned int base;
} __attribute__((packed));

struct IDT_DESCRIPTOR IDT[256];
struct IDT_BASE IDT_BASE;

unsigned char IRQ_MASTER_MASK = 0xff;
unsigned char IRQ_SLAVE_MASK = 0xff;

void PIC_remap() {
  // ICW1
  outb(0x20, 0x11);
  in_out_wait();
  outb(0xA0, 0x11);
  in_out_wait();

  // ICW2
  outb(0x21, 0x20);
  in_out_wait();
  outb(0xA1, 0x20);
  in_out_wait();

  // ICW3
  outb(0x21, 0x04);
  in_out_wait();
  outb(0xA1, 0x02);
  in_out_wait();

  // ICW4
  outb(0x21, 0x01);
  in_out_wait();
  outb(0xA1, 0x01);
  in_out_wait();

  outb(0x21, 0b11111100);
  in_out_wait();
  outb(0xA1, 0xFF);
  in_out_wait();

  PIC_set_mask(0b1111111, 0xFF);
}

void IDT_reg_handler(int number, unsigned short segm_selector,
                     unsigned short flags, intr_handler handler) {
  unsigned int handler_addr = (unsigned int)handler;
  IDT[number].addr_low_bits = (unsigned short)(handler_addr & 0xFFFF);
  IDT[number].segm_selector = segm_selector;
  IDT[number].nulls = 0;
  IDT[number].flags = flags;
  IDT[number].addr_high_bits = (unsigned short)(handler_addr >> 16);
}

void PIC_set_mask(unsigned char master, unsigned char slave) {
  outb(0x21, master);
  outb(0xA1, slave);
}

void PIC_update_mask(unsigned char ms_sl, unsigned char bit,
                     unsigned char value) {
  if (ms_sl == 0) {
    if (value) {
      IRQ_MASTER_MASK |= (1 << bit);
    } else {
      IRQ_MASTER_MASK &= ~(1 << bit);
    }
  } else if (ms_sl == 1) {
    if (value) {
      IRQ_SLAVE_MASK |= (1 << bit);
    } else {
      IRQ_SLAVE_MASK &= ~(1 << bit);
    }
  }
  PIC_set_mask(IRQ_MASTER_MASK, IRQ_SLAVE_MASK);
}

void load_IDT() {
  int IDT_COUNT = sizeof(IDT) / sizeof(IDT[0]);
  IDT_BASE.base = (unsigned int)(&IDT[0]);
  IDT_BASE.limit = (sizeof(struct IDT_DESCRIPTOR) * IDT_COUNT) - 1;
  asm("lidt %0" : : "m"(IDT));
}
