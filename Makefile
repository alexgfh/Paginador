CC=gcc

mmu:
	gcc -Wall block_heap.c frame_queue.c page_table_list.c pager.c page_table.c mmu.a -lpthread -o mmu

test1:
	gcc -Wall test1.c uvm.a -lpthread -o test1
	
test2:
	gcc -Wall test2.c uvm.a -lpthread -o test2
	
test3:
	gcc -Wall test3.c uvm.a -lpthread -o test3

test4:
	gcc -Wall test4.c uvm.a -lpthread -o test4

test5:
	gcc -Wall test5.c uvm.a -lpthread -o test5

test6:
	gcc -Wall test6.c uvm.a -lpthread -o test6

clean:
	rm -rf mmu.pmem.*
	rm -rf mmu.log.*
	rm -rf uvm.log.*
	rm -f mmu
	rm -f mmu.sock
	rm -f test6
	rm -f test5
	rm -f test4
	rm -f test3
	rm -f test2
	rm -f test1
	rm -f *~
