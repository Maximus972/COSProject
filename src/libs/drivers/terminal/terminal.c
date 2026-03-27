char *vidptr = (char *)0xB8000; // Видеобуффер

/**
 * Функция, выводящая на по определенным
 * координатам экрана символ
 * @param x Координата x на экране
 * @param y Координата y на экране
 * @param character Символ, выводимый на экран
 */
void print_char(int x, int y, char character) {
  int pointSymbol = (y * 80 + x) * 2;
  int pointAttribute = pointSymbol + 1;
  vidptr[pointSymbol] = character;
  vidptr[pointAttribute] = 0x07;
}

void loading_movement(int x, int y,
                      int attribute) { // Функция вывода на экран загрузки
  const char *loading = "\\|/-\\\0";
  int i = (y * 80 + x) * 2;
  int j = 0;
  while (loading[j] != '\0') {
    vidptr[i] = loading[j];    // Символ
    vidptr[i + 1] = attribute; // Атрибут
    ++j;
    // i = i + 2;
    if (loading[j] == '\0') {
      j = j - 4;
    }
    int count = 0;
    while (count <= 50000000) {
      asm volatile("" :::);
      count = count + 1;
    }
  }
}
