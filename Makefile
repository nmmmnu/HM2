CC   = gcc -Wall -c
LINK = gcc -o



all: test_hm_ve test_hm_ll test_hm_file_ve test_hm_file_ll



clean:
	rm -f *.o test_hm_ve test_hm_ll test_hm_filehm_list.o



malloc_info.o: malloc_info.c malloc_info.h
	$(CC) malloc_info.c



test_hm_ve:			test_hm.o hm_pair.o malloc_info.o	hm_vector.o hm_list_vector.o
	$(LINK) test_hm_ve	test_hm.o hm_pair.o malloc_info.o	hm_vector.o hm_list_vector.o

test_hm_ll:			test_hm.o hm_pair.o malloc_info.o	hm_linklist.o hm_list_linklist.o
	$(LINK) test_hm_ll	test_hm.o hm_pair.o malloc_info.o	hm_linklist.o hm_list_linklist.o

test_hm.o: test_hm.c		hm_pair.h hm_list.h malloc_info.h	hm_vector.h hm_linklist.h
	$(CC) test_hm.c



test_hm_file_ve:		test_hm_file.o hm_pair.o malloc_info.o	hm_vector.o hm_list_vector.o
	$(LINK) test_hm_file_ve	test_hm_file.o hm_pair.o malloc_info.o	hm_vector.o hm_list_vector.o

test_hm_file_ll:		test_hm_file.o hm_pair.o malloc_info.o	hm_linklist.o hm_list_linklist.o
	$(LINK) test_hm_file_ll	test_hm_file.o hm_pair.o malloc_info.o	hm_linklist.o hm_list_linklist.o

test_hm_file.o: test_hm_file.c	hm_pair.h hm_list.h malloc_info.h	hm_vector.h hm_linklist.h
	$(CC) test_hm_file.c



hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_vector.o: hm_vector.c hm_vector.h hm_pair.h
	$(CC) hm_vector.c

hm_list_vector.o: hm_list_vector.c hm_list.h hm_vector.h hm_pair.h
	$(CC) hm_list_vector.c



hm_linklist.o: hm_linklist.c hm_linklist.h hm_pair.h
	$(CC) hm_linklist.c

hm_list_linklist.o: hm_list_linklist.c hm_list.h hm_linklist.h hm_pair.h
	$(CC) hm_list_linklist.c

