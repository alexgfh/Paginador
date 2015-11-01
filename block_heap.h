#ifndef block_heap_H
#define block_heap_H

#include <sys/types.h>

void init_block_heap(int nblocks);

/* Returns 1 if there's at least one available block, else returns 0. */
int has_freeblock();

/* Returns an available block, if there is none, returns -1. */
int get_block();

void free_block(int block);

void destroy_block_heap();

#endif
