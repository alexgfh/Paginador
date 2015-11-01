CC=gcc

mmu:
	gcc -Wall block_heap.c frame_queue.c page_table_list.c pager.c page_table.c mmu.a -lpthread -o mmu

test6:
	gcc -Wall test6.c uvm.a -lpthread -o test6

clean:
	rm -rf mmu.pmem.*
	rm -rf mmu.log.*
	rm -rf uvm.log.*
	rm -f mmu
	rm -f mmu.sock
	rm -f test6
