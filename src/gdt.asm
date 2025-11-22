global gdt_init

section .data

; TODO: Переделать таблицу, узнать каким образом
gdt_base: ; GDT задает здесь плоскую модель памяти.
    dd 0x00000000
    dd 0x00000000

gdt_code:
    dd 0x0000FFFF
    dd 0x00CF9A00

gdt_data:
    dd 0x0000FFFF
    dd 0x00CF9200

gdt_end:

gdt:
    dw gdt_end - gdt_base - 1
    dd gdt_base

CODE_SEL equ gdt_code - gdt_base
DATA_SEL equ gdt_data - gdt_base

section .text

gdt_init:
    
    lgdt [gdt]

    mov ax, DATA_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax ;! Стек растет вниз, а тут база стека по адресу 0, куда ему вниз расти???

    jmp CODE_SEL:.reload_cs

.reload_cs:
    ret


