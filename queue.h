#ifndef frame_queue_H
#define frame_queue_H

//TODO: Add Second Chance algorithm to this queue
typedef struct Node {
	struct Node *prev;
	struct Node *next;
	unsigned int key;
	unsigned int free_frames;
} Node;

void init_queue(Node** end);

Node *find(unsigned int key, Node* end);

int contain(unsigned int key, Node* end);

void pop(Node* end);

Node* push(unsigned int key, Node* end);

void put_on_top(unsigned int key, Node* end);

void clear(Node *end);

#endif
