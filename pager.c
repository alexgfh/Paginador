#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include "pager.h"
#include "mmu.h"
#include "frame_queue.h"
#include "page_table_list.h"
#include "page_table.h"
#include "block_heap.h"


/*
#define is_mapped(frame) frame&1
#define set_mapped(frame) frame|=1
#define set_unmapped(frame) frame&=0

#define is_referenced(frame) frame&2
#define set_referenced(frame) frame|=2
#define set_unreferenced(Frame) frame&=(~2)

#define set_frame(frame, value) frame=value<<12
#define get_frame(frame) frame&(~1<<31)

#define is_block_used(block) block&1
#define set_block_used(block) block|=1
#define set_block_unused(block) block&=0
*/
unsigned int* frame_table; //maps frame to block and stores frame info [0~num_frames]

void pager_init(int nframes, int nblocks) {
	init_queue(nframes);
	init_block_heap(nblocks);
	init_page_table_list();
}

void pager_create(pid_t pid) {
	page_table_list_append(pid);
}

void *pager_extend(pid_t pid) {
    int block = get_block();
    if (block<0) return NULL;
    struct pagetable* page_table = get_page_table(pid);
    int page = get_new_page(page_table, block);
    return (void*)(UVM_BASEADDR + (intptr_t)(page<<12));
}

void pager_fault(pid_t pid, void *addr) {
    struct pagetable* page_table = get_page_table(pid);
    int page_no = get_page_no(addr);
    if(page_has_frame(page_table, page_no)) {
        int frame = page_table->page_frames[page_no];
        mmu_chprot(pid, addr, PROT_READ | PROT_WRITE);
        set_frame_referenced(frame);
    }
    else {
        int new_frame = get_frame();
        if(page_has_block(page_table, page_no)) {
            int block = page_table->blocks[page_no];
            mmu_disk_read(block, new_frame);
            free_block(block);
        }
        page_table->page_frames[page_no] = new_frame;
        mmu_zero_fill(new_frame);
        mmu_resident(pid, addr, new_frame, PROT_READ | PROT_WRITE);
    }
}


int pager_syslog(pid_t pid, void *addr, size_t len) {
    char *message = (char*)malloc(len+1);
    struct pagetable* page_table = get_page_table(pid);
    int i=0, m=0;
    
    for(i=0; i < len; i++)
    {
      // if pid doest not have permission to access addr+i
      // return -1
      if(!has_permission(page_table, (intptr_t)addr+i)) return -1;
      message[m++]=pmem[((intptr_t)addr-UVM_BASEADDR)+i];
    }
    printf("pager_syslog pid %d %s\n", (int)pid, message);
    return 0;
}

void pager_destroy(pid_t pid) {
    page_table_list_remove(pid);
}
