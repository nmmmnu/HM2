CC   = gcc -Wall -g -O0 -c
LINK = gcc -o
LIBS =
#-ljemalloc



all: test_hm_ve				test_hm_file_ve

# test_hm_ll test_hm_ha		test_hm_file_ll test_hm_file_ha


clean:
	rm -f *.o	test_hm_ve test_hm_ll test_hm_ha	test_hm_file_ve test_hm_file_ll test_hm_file_ha



test_hm_ve:			test_hm.o hm_pair.o	hm_vector.o
	$(LINK) test_hm_ve	test_hm.o hm_pair.o	hm_vector.o					$(LIBS)

test_hm_ll:			test_hm.o hm_pair.o	hm_linklist.o hm_list_linklist.o
	$(LINK) test_hm_ll	test_hm.o hm_pair.o	hm_linklist.o hm_list_linklist.o		$(LIBS)

test_hm_ha:			test_hm.o hm_pair.o	hm_hash.o hm_list_hash.o hm_vector.o
	$(LINK) test_hm_ha	test_hm.o hm_pair.o	hm_hash.o hm_list_hash.o hm_vector.o		$(LIBS)

test_hm.o: test_hm.c		hm_pair.h hm_list.h	hm_vector.h hm_linklist.h hm_hash.h
	$(CC) test_hm.c



test_hm_file_ve:		test_hm_file.o hm_pair.o	hm_vector.o
	$(LINK) test_hm_file_ve	test_hm_file.o hm_pair.o	hm_vector.o				$(LIBS)

test_hm_file_ll:		test_hm_file.o hm_pair.o	hm_linklist.o hm_list_linklist.o
	$(LINK) test_hm_file_ll	test_hm_file.o hm_pair.o	hm_linklist.o hm_list_linklist.o		$(LIBS)

test_hm_file_ha:		test_hm_file.o hm_pair.o	hm_hash.o hm_list_hash.o	hm_vector.o
	$(LINK) test_hm_file_ha	test_hm_file.o hm_pair.o	hm_hash.o hm_list_hash.o	hm_vector.o	$(LIBS)

test_hm_file.o: test_hm_file.c	hm_pair.h hm_list.h		hm_vector.h hm_linklist.h hm_hash.h
	$(CC) test_hm_file.c



hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_vector.o: hm_vector.c hm_vector.h hm_list.h
	$(CC) hm_vector.c

hm_linklist.o: hm_linklist.c hm_linklist.h hm_pair.h
	$(CC) hm_linklist.c

hm_hash.o: hm_hash.c hm_hash.h hm_pair.h hm_vector.h
	$(CC) hm_hash.c


