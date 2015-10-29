#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "page_table.h"
#include "mmu.h"

struct pagetable* create_page_table() {
    int pagesize = sysconf(_SC_PAGESIZE);
    int addr_space_size = UVM_MAXADDR - UVM_BASEADDR + 1;
	int num_pages = addr_space_size/pagesize; //256 for 4KiB pages
	
    struct pagetable* page_table = malloc(sizeof(struct pagetable));
    page_table->num_pages = num_pages;
    page_table->page_frames = malloc(num_pages*sizeof(int));
    page_table->next_free_page = 0;
    
    return page_table;
}

/* Returns page number (not vaddr) */
int get_new_page(struct pagetable* page_table) {
    int page_number = page_table->next_free_page;
    page_table->next_free_page++;
    return page_number;
}

/* Converts from page number to vaddr */
int* get_page_address(int page) {
    return (int*)(UVM_BASEADDR + (intptr_t)(page<<12));
}

int get_page_frame(struct pagetable* page_table, int page) {
    return page_table->page_frames[page];
}

void destroy_page_table(struct pagetable* page_table) {
    free(page_table->page_frames);
    free(page_table);
}
