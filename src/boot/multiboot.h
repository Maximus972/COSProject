
#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#include "libs/types/types.h"

typedef struct {
  uint_32 flags;
  uint_32 mem_lower;
  uint_32 mem_upper;
} boot __attribute__((packed));

#endif
