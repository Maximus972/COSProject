#include "libs/libc/string.h"
#include "libs/types/types.h"

static char *digits = "0123456789ABCDEF";

void itoa(unsigned int value, Buffer *buffer, unsigned char base) {
  // 1. Считаем, сколько будет цифр. Минимум одна — это сразу
  //    обрабатывает случай value == 0 (отдельный if не нужен).
  size_t n = 1;
  for (unsigned int v = value; v >= base; v /= base) {
    n++;
  }

  // 2. Защита через capacity: n цифр + '\0' обязаны влезть в чужое
  //    хранилище. Не влезает — не портим память, пишем пустую строку.
  if (n + 1 > buffer->capacity) {
    buffer->data[0] = '\0';
    buffer->length = 0;
    return;
  }

  // 3. Пишем цифры от конца к началу: младшая (value % base) ложится
  //    в data[n-1], старшая — в data[0]. Порядок сразу правильный.
  size_t i = n;
  do {
    i--;
    buffer->data[i] = digits[value % base];
    value /= base;
  } while (i != 0);

  // 4. Терминатор строки и фактическая длина.
  buffer->data[n] = '\0';
  buffer->length = n;
}
