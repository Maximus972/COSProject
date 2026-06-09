
#ifndef LIBC_H
#define LIBC_H

#include "libs/util/buffer.h"
// struct Buffer {
//   int length,
//
// }
void itoa(unsigned int value, Buffer *buffer, unsigned char base);

#endif
