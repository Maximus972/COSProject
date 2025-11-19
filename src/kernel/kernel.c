/* kernel.c */
#include "../gdt.h"

char *vidptr = (char*)0xB8000; // Видеобуффер
int x_coordinate = 0;
int y_coordinate = 0;

void printChar(int x, int y, char character) {
    int pointSymbol = y * 80 + x * 2;
    int pointAttribute = pointSymbol + 1;
    vidptr[pointSymbol] = character;
    vidptr[pointAttribute] = 0x07;
}

void loading_movement(int x, int y, int attribute) { //Функция вывода на экран загрузки
    const char *loading = "\\|/-\\\0";
    int i = y * 80 + x * 2;
    int j = 0;
    while (loading[j] != '\0') {
        vidptr[i] = loading[j];   // Символ
        vidptr[i + 1] = attribute;   // Атрибут
        ++j;
        // i = i + 2;
        if (loading[j] == '\0') {
            j = j - 4;
        }
        int count = 0;
        while (count <= 50000000)
        {
            asm volatile("" :::);
            count = count + 1;
        }
    }
}

void wait(int count_max) {
    int count = 0; 
    while (count <= count_max) {
        asm volatile("" :::);
        count = count + 1;
    }
}

/* Объявляем функцию, которая принимает аргументы от GRUB (пока не используем) */
void kmain(void) {

    printChar(50, 22, 'C');

    wait(500000000);

    gdt_init();

    wait(500000000);

    printChar(30, 11, 'B');

    wait(500000000);

    loading_movement(25, 25, 0x07);

    return;
}
