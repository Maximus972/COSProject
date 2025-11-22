#ifndef ASM_BASE_FUNCTIONS
#define ASM_BASE_FUNCTIONS

extern void in_out_wait(void);
extern void outb(unsigned short port, unsigned char byte);
extern void outw(unsigned short port, unsigned short word);
extern void outd(unsigned short port, unsigned int dword);
extern unsigned char inb(unsigned short port);
extern unsigned short inw(unsigned short port);
extern unsigned int ind(unsigned short port);

#endif