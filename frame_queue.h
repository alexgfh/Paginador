#ifndef queue_H
#define queue_H

void init_queue(int size_limit);

int get_frame(pid_t pid, int page_no);

int is_frame_mapped(int frameno);

void set_frame_referenced(int frameno);

void free_frame(int frameno);

void destroy_queue();

#endif
