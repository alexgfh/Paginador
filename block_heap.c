#include <stdlib.h>
#include <stdio.h>
#include "block_heap.h"

static int* block_heap = NULL;
static int size;
static int free_blocks;

void init_block_heap(int nblocks) {
    printf("NUMERO BLOCOS %d\n", nblocks);
    if (block_heap!=NULL) {
        fprintf(stderr, "block_heap already initialized.");
        exit(1);
    }
    block_heap = calloc(nblocks, sizeof(int)); //zero initialize
    size = free_blocks = nblocks;
}

int has_freeblock() {
    return free_blocks>0;
}

int get_block() {
    /* Check for reservations. */
    if(free_blocks == 0) {
        return -1;
    }
    
    /* Get first available block */
    int i=0; 
    printf("SIZE %d\n", size);
    for (i = 0; i<size; i++) {
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

void destroy_block_heap() {
    free(block_heap);
    block_heap = NULL;
}
