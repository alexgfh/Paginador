#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "page_table.h"
#include "frame_queue.h"
#include "mmu.h"

struct pagetable* create_page_table() {
    int pagesize = sysconf(_SC_PAGESIZE);
    int addr_space_size = UVM_MAXADDR - UVM_BASEADDR + 1;
  	int num_pages = addr_space_size/pagesize; //256 for 4KiB pages
    	
    struct pagetable* page_table = malloc(sizeof(struct pagetable));
    page_table->num_pages = num_pages;
    page_table->page_frames = (int*)malloc(num_pages*sizeof(int));
    page_table->blocks = (int*)malloc(num_pages*sizeof(int));
    int i;
    for(i=0;i<num_pages;i++) {
        page_table->page_frames[i]=page_table->blocks[i]=-1;
    }
    page_table->next_free_page = 0;
    page_table->page_size = pagesize;
    
    return page_table;
}

int has_permission(struct pagetable* page_table, intptr_t addr)
{
  int i=0;
  for(;i<page_table->next_free_page; i++)
    if((addr-UVM_BASEADDR)>>12==page_table->page_frames[i]) return 1;
  return 0;
}

/* Returns page number (not vaddr) */
int get_new_page(struct pagetable* page_table, int block) {
    int page_number = page_table->next_free_page;
    page_table->next_free_page++;
    page_table->blocks[page_number]=block;
    return page_number;
}

/* Converts from page number to vaddr */
int* get_page_address(int page) {
    return (int*)(UVM_BASEADDR + (intptr_t)(page<<12));
}

/* Converts from vaddr to page number */
int get_page_no(void* addr) {
    return (((intptr_t)addr-UVM_BASEADDR)>>12);
}

int page_has_frame(struct pagetable* page_table, int page) {
    return page_table->page_frames[page]!=-1;
}

int page_has_block(struct pagetable* page_table, int page) {
    return page_table->page_frames[page]!=-1;
}

void destroy_page_table(struct pagetable* page_table) {
    int i=0;
    
    // Freeing all blocks allocated
    for(i=0; i < page_table->next_free_page; i++) {
      free_frame(page_table->page_frames[i]);
      free_block(page_table->blocks[i]);
    }
    free(page_table->page_frames);
    free(page_table->blocks);
    free(page_table);
}
