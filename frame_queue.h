#ifndef queue_H
#define queue_H

void init_queue(int size_limit);

int get_frame();

void free_frame(int frameno);

void destroy_queue();

#endif
