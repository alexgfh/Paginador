#ifndef page_table_list_H
#define page_table_list_H

#include <sys/types.h>
#include "page_table.h"

/* Stores one page table for each process */

void init_page_table_list();

void page_table_list_append(pid_t pid);

void page_table_list_remove(pid_t pid);

struct pagetable* get_page_table(pid_t pid);

void destroy_process_list();

#endif
