#include "page_table_list.h"
#include <stdio.h>

struct pid_pagetable {
    pid_t pid; //key
    struct* pagetable; //value
}

static int size;

static struct pid_pagetable* table_list;

void init_page_table_list() {
    size = 1;
    table_list = calloc(size,sizeof(struct pid_pagetable));
}

void page_table_list_append(pid_t pid) {
    int found = 0;
    
    /* Try to find a previously removed space */
    for (i = 0; i<size; i++) {
        if (table_list[i].pagetable == NULL) {
            table_list[i].pid = pid;
            table_list[i].pagetable = create_page_table();
            found = 1;
            break;
        }
    }
    if (!found) { /* Increase the list size */
        size*=2;
        table_list = realloc(table_list, size*sizeof(pid_pagetable));
        table_list[size+1].pid = pid;
        table_list[size+1].pagetable = create_page_table();
    }
}

void page_table_list_remove(pid_t pid) {
    for (int i = 0; i<size; i++) {
        if (table_list[i].pid == pid) {
            table_list[i].pid = 0;
            destroy_page_table(table_list[i].pagetable);
            table_list[i].pagetable = NULL;
        }
    }
}

struct pagetable* get_page_table(pid_t pid) {
    for (int i = 0; i<size; i++) {
        if (table_list[i].pid == pid) {
            return table_list[i].pagetable;
        }
    }
    fprintf(stderr, "process wasn't added to page_table_list.");
    exit(1);
    
}

void destroy_process_list() {
    for (int i = 0; i<size; i++) {
        if (table_list[i].pagetable != NULL) {
            free(table_list[i].pagetable);
        }
    }
    free(table_list);
}
