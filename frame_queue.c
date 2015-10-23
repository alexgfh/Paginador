#include <stdlib.h>

#include "queue.h"

Node* push(unsigned int key, Node* end){
	Node *q=(Node *)malloc(sizeof(Node));
	q->prev=end->prev;
	q->prev->next=q;
	q->next=end;
	end->prev=q;
	q->key=key;
	end->free_frames--;
	return q;
}

void init_queue(Node** end, int size_limit){
	(*end)=(Node *)malloc(sizeof(Node));
	(*end)->next=(*end);
	(*end)->prev=(*end);
	(*end)->free_frames = size_limit;
}

Node* find(unsigned int key, Node* end){
	Node *aux = end->next;
	
	while(aux!=end && aux->key!=key)
		aux=aux->next;
	
	return aux==end?NULL:aux;
}

int contain(unsigned int key, Node* end){
	Node *aux = find(key, end);
	
	return aux==NULL?0:1;
}

void pop(Node *end){
	if(end->next!=end){
		Node *aux = end->next;
		end->next= aux->next;
		aux->next->prev=end;
		free(aux);
		end->free_frames++;
	}
}

void put_on_top(unsigned int key, Node* end){
	Node *aux =find(key, end);
	aux->next->prev=aux->prev;
	aux->prev->next=aux->next;
	aux->prev=aux->next=NULL;
	free(aux);
	push(key, end);
}

void clear(Node *end){
	Node *aux = end->prev;
	while(aux!=end){
		aux=aux->prev; free(aux->next);
	}
	free(end);
}

