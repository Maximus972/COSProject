#!/bin/bash

# build.sh

# Создаем папку для объектных файлов
mkdir -p obj

# Ассемблируем multiboot.asm
nasm -f elf32 -o obj/multiboot.o src/boot/multiboot.asm

# Ассемблируем gdt.asm
nasm -f elf32 -o obj/gdt.o src/gdt.asm

# Компилируем kernel.c
gcc -m32 -ffreestanding -nostdlib -nostartfiles -nostdinc -c src/kernel/kernel.c -o obj/kernel.o

# Линкуем все вместе, используя скрипт
ld -m elf_i386 -T link.ld -o obj/kernel.elf obj/multiboot.o obj/kernel.o obj/gdt.o

# Создаем загрузочный образ
mkdir -p isodir/boot/grub
cp obj/kernel.elf isodir/boot/kernel.elf

# Создаем конфигурационный файл GRUB
echo 'menuentry "my_os" {
    multiboot /boot/kernel.elf
}' > isodir/boot/grub/grub.cfg

# Создаем образ ISO
grub-mkrescue -o my_os.iso isodir

# Запускаем в QEMU
qemu-system-x86_64 -cdrom my_os.iso //TODO: Заменить скрипты сборки на Makefile