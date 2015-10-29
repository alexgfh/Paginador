#include <stdlib.h>

#include "frame_queue.h"

static int* frame_queue; //inverted index, circular queue
static int frame;
static int size;

#define is_referenced(mask) mask&1
#define set_referenced(mask) mask|=1
#define unset_referenced(mask) mask&=(~1)

#define is_mapped(mask) mask&(2)
#define set_mapped(mask) mask|=(2)
#define unset_mapped(mask) mask&=(~2)


void init_queue(int size_limit){
	frame_queue = calloc(size_limit,sizeof(int));
	frame = 0;
	size = size_limit;
}

int get_frame(){
	//Second-chance algorithm
	while (1) {
		int ret = -1;
		if(!is_referenced(frame_queue[frame])) {
			ret = frame;
			if(is_mapped(frame_queue[frame])) {
				/*TODO: save frame to disk
				 *save block_number on frame_queue[frame] */
			}
			set_mapped(frame_queue[frame]);
			set_referenced(frame_queue[frame]);
		}
		frame++;
		frame %= size;
		if(ret!=-1) return ret;
		unset_referenced(frame_queue[frame]);
	}
	return -1; //error
}

void free_frame(int frameno) {
	frame_queue[frameno] = 0; //clear all fields
}

void destroy_queue(){
	free(frame_queue);
}

