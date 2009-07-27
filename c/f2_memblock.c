#include "funk2.h"

// funk2_memblock

void funk2_memblock__init(funk2_memblock_t* block, f2size_t byte_num, int used, int gc_touch) {
  funk2_memblock__byte_num(block) = byte_num;
  block->used                     = used;
  block->gc_touch                 = gc_touch;
  block->generation_num           = 0;
}


