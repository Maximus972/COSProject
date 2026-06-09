#ifndef BUFFER_H
#define BUFFER_H

#include "libs/types/types.h"

typedef struct {
  size_t capacity;
  size_t length;
  char *data;
} Buffer;

void buffer_init(Buffer *b, char *storage, size_t cap);

#endif
