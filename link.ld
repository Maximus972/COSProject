/* link.ld */
OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

SECTIONS
{
    . = 0x00100000;          /* Адрес загрузки ядра */

    .multiboot ALIGN(4) : {
        KEEP(*(.multiboot))  /* Обязательно сохраняем Multiboot-заголовок */
    }

    .text : {
        *(.text)             /* Код */
        *(.text*)
        *(.rodata)           /* Только для чтения данные */
        *(.rodata*)
    }

    .data ALIGN(4096) : {
        *(.data)
        *(.data*)
    }

    .bss ALIGN(4096) : {
        *(COMMON)
        *(.bss)
        *(.bss*)
    }
}