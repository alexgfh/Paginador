#ifndef page_table_H
#define page_table_H

#include <sys/types.h>

struct pagetable {
    int num_pages;
    int* page_frames; //maps from page_no to frame_no
    int next_free_page;
};

struct pagetable* create_page_table();

int get_new_page(struct pagetable* page_table);

int* get_page_address(int page);

int get_page_frame(struct pagetable* page_table, int page);

void destroy_page_table(struct pagetable* page_table);

#endif 
