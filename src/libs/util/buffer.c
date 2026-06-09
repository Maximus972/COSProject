#include "libs/util/buffer.h"

void buffer_init(Buffer *b, char *storage, size_t cap) {
  b->capacity = cap;
  b->length = 0;
  b->data = storage;
}
