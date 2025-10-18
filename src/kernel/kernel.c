/* kernel.c */

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

// void clear_terminal() {
//     reset_coordinates();
//     int legth_coordinates = y_coordinate * 80 + x_coordinate * 2;
//     while (legth_coordinates < 80 * 25 * 2) {
//         vidptr[legth_coordinates] = ' ';     // Символ пробела
//         vidptr[legth_coordinates + 1] = 0x07;  // Атрибут: светло-серый на черном
//         legth_coordinates = legth_coordinates + 2;
//     }
// }

// void reset_coordinates() {
//     x_coordinate = 0;
//     y_coordinate = 0;
// }

// void printf(char *string) {
//     int i = 0; 
//     while (string[i] != '\0') {
//         printChar();
//     }
// } 

void wait(int count_max) {
    int count = 0; 
    while (count <= count_max) {
        asm volatile("" :::);
        count = count + 1;
    }
}

/* Объявляем функцию, которая принимает аргументы от GRUB (пока не используем) */
void kmain(void) {
    /* Указатель на видеопамять VGA-буфера */
    // const char *str = "Hello, GRUB World!\n";
    
    /* Очищаем экран: 25 строк по 80 символов, каждый символ - 2 байта */

    printChar(50, 22, 'C');


    // wait(500000000000000);


    printChar(30, 11, 'B');

    loading_movement(25, 25, 0x07);

    // loading_movement(25, 60, 0x07);

    // j = 0;

    // /* Выводим строку в видеопамять */
    // while (str[j] != '\0') {
    //     vidptr[i] = str[j];   // Символ
    //     vidptr[i+1] = 0x07;   // Атрибут
    //     ++j;
    //     i = i + 2;
    // }

    // /* Очищаем экран: 25 строк по 80 символов, каждый символ - 2 байта */
    // while (j < 80 * 25 * 2) {
    //     vidptr[j] = ' ';     // Символ пробела
    //     vidptr[j + 1] = 0x07;  // Атрибут: светло-серый на черном
    //     j = j + 2;
    // }

    return;
}
