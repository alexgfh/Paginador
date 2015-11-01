CC=gcc

mmu:
	gcc block_heap.c frame_queue.c page_table_list.c pager.c page_table.c mmu.a -lpthread -o mmu

test6:
	gcc test6.c uvm.a -lpthread -o test6

