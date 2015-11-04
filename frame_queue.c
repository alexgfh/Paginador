#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include "page_table_list.h"
#include "page_table.h"
#include "mmu.h"
#include "frame_queue.h"

struct frame_info {
    pid_t pid;
    int page_no;
    int mapped;
    int referenced;
};

static struct frame_info* frame_queue; //inverted index, circular queue
static int frame;
static int size;

/*
#define is_referenced(mask) mask&1
#define set_referenced(mask) mask|=1
#define unset_referenced(mask) mask&=(~1)

#define is_mapped(mask) mask&(2)
#define set_mapped(mask) mask|=(2)
#define unset_mapped(mask) mask&=(~2)

#define get_page_no(mask) mask>>2
#define set_page_no(mask, pageno) mask=mask&3;mask|=(pageno<<2)
*/
void init_queue(int size_limit){
	frame_queue = calloc(size_limit,sizeof(struct frame_info));
	frame = 0;
	size = size_limit;
}

int get_frame(pid_t pid, int page_no){
	//Second-chance algorithm
	while (1) {
		int ret = -1;
		if(!frame_queue[frame].referenced) {
		    //fprintf(stderr, "ret:%d, referenced:%d\n", frame, frame_queue[frame].referenced);
			ret = frame;
			if(frame_queue[frame].mapped) {
			    //save frame to disk
			    int out_pid = frame_queue[frame].pid;
	    		    int out_page_no = frame_queue[frame].page_no;
	    			
		            //fprintf(stderr, "out_pid: %d\n", out_pid);
	    		    struct pagetable* out_page_table = get_page_table(out_pid);
			    int block = out_page_table->blocks[out_page_no];
			    printf("out_pid:%d\n", frame_queue[frame].pid);
                printf("out_page_no:%d, frame:%d, block:%d\n",out_page_no, frame, block);
			    mmu_disk_write(frame, block);
			    mmu_nonresident(pid, get_page_address(out_page_no));
			    out_page_table->page_frames[page_no]=-1;
			    
			    
				/*TODO: save frame to disk
				 *save block_number on frame_queue[frame] */
			}
			//inverse mapping from frame to vaddr
			frame_queue[frame].pid = pid;
			frame_queue[frame].page_no = page_no;
			frame_queue[frame].mapped=1;
			frame_queue[frame].referenced=1;
		}
		
		frame_queue[frame].referenced=0;
		//mmu_resident(frame_queue[frame].pid, get_page_address(frame_queue[frame].page_no), frame, PROT_NONE);
		frame++;
		
		frame %= size;
		
		if(ret!=-1) {return ret;}
	}
	return -1; //error
}

int is_frame_mapped(int frameno) {
    return frame_queue[frameno].mapped;
}

void set_frame_referenced(int frameno) {
    frame_queue[frameno].referenced=1;
}

void free_frame(int frameno) {
    //clear all fields
	frame_queue[frameno].pid=0;
	frame_queue[frameno].page_no=0;
	frame_queue[frameno].mapped=0;
	frame_queue[frameno].referenced=0;
}

void save_to_disk(int frameno) {
    int out_pid = frame_queue[frame].pid;
	int out_page_no = frame_queue[frame].page_no;
	struct pagetable* out_page_table = get_page_table(out_pid);
    int block = out_page_table->blocks[out_page_no];
	mmu_disk_write(frame, block);
	mmu_nonresident(out_pid, get_page_address(out_page_no));
	out_page_table->page_frames[out_page_no]=-1;
}

void destroy_queue(){
	free(frame_queue);
}

