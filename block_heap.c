#include <stdlib.h>
#include <stdio.h>
#include "block_heap.h"

static int* block_heap = NULL;
static int size;
static int free_blocks;
static int reserved_blocks;

void init_block_heap(int nblocks) {
    if (block_heap!=NULL) {
        fprintf(stderr, "block_heap already initialized.");
        exit(1);
    }
    block_heap = calloc(nblocks, sizeof(int)); //zero initialize
    size = free_blocks = nblocks;
    reserved_blocks = 0;
}

int has_freeblock() {
    return (free_blocks - reserved_blocks)>0;
}

int get_block() {
    /* Check for reservations. */
    if((free_blocks - reserved_blocks) == 0) {
        return -1;
    }
    
    /* Get first available block */
    for (int i = 0; i<size; i++) {
        if(block_heap[i]==0) {
            block_heap[i]=1; //mark as used
            free_blocks--;
            return i;
        }
    }
    return -1;
}

void free_block(int block) {
    block_heap[block] = 0;
    free_blocks++;
}

/* Pre-condition: there is at least one free block. */
void reserve_block() {
    if(!has_free_block()) {
        fprintf(stderr, "Before reserving a block, it must be checked if there's a free one.");
        exit(1);
    }
    reserved_blocks++;
}

void remove_reservation() {
    if (reserved_blocks == 0) {
        fprintf(stderr, "no reserved blocks.");
        exit(1);
    }
    reserved_blocks--;
}

void destroy_block_heap() {
    free(block_heap);
    block_heap = NULL;
}

#endif
