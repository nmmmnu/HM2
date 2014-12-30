CC   = gcc -Wall -g -O0 -c
LINK = gcc -o
LIBS =
#-ljemalloc



all: test_hm_ve test_hm_ll	test_hm_file_ve test_hm_file_ll

#  test_hm_ha 		 test_hm_file_ll test_hm_file_ha


clean:
	rm -f *.o	test_hm_ve test_hm_ll test_hm_ha	test_hm_file_ve test_hm_file_ll test_hm_file_ha



test_hm_ve:			test_hm_ve.o hm_pair.o		hm_vector.o
	$(LINK) test_hm_ve	test_hm_ve.o hm_pair.o		hm_vector.o				$(LIBS)

test_hm_ve.o: test_hm.c		hm_pair.h hm_list.h test_hm_factory.h		hm_vector.h
	$(CC) test_hm.c -D USE_VECTOR
	mv test_hm.o test_hm_ve.o


test_hm_ll:			test_hm_ll.o hm_pair.o	hm_linklist.o
	$(LINK) test_hm_ll	test_hm_ll.o hm_pair.o	hm_linklist.o					$(LIBS)

test_hm_ll.o: test_hm.c		hm_pair.h hm_list.h test_hm_factory.h		hm_linklist.h
	$(CC) test_hm.c -D USE_LINKLIST
	mv test_hm.o test_hm_ll.o


test_hm_ha:			test_hm.o hm_pair.o	hm_hash.o hm_list_hash.o hm_vector.o
	$(LINK) test_hm_ha	test_hm.o hm_pair.o	hm_hash.o hm_list_hash.o hm_vector.o		$(LIBS)



test_hm_file_ve:		test_hm_file_ve.o hm_pair.o	hm_vector.o
	$(LINK) test_hm_file_ve	test_hm_file_ve.o hm_pair.o	hm_vector.o				$(LIBS)

test_hm_file_ve.o: test_hm_file.c	hm_pair.h hm_list.h test_hm_factory.h	hm_vector.h
	$(CC) test_hm_file.c -D USE_VECTOR
	mv test_hm_file.o test_hm_file_ve.o


test_hm_file_ll:		test_hm_file_ll.o hm_pair.o	hm_linklist.o
	$(LINK) test_hm_file_ll	test_hm_file_ll.o hm_pair.o	hm_linklist.o				$(LIBS)

test_hm_file_ll.o: test_hm_file.c	hm_pair.h hm_list.h test_hm_factory.h	hm_linklist.h
	$(CC) test_hm_file.c -D USE_LINKLIST
	mv test_hm_file.o test_hm_file_ll.o

test_hm_file_ha:		test_hm_file.o hm_pair.o	hm_hash.o hm_list_hash.o	hm_vector.o
	$(LINK) test_hm_file_ha	test_hm_file.o hm_pair.o	hm_hash.o hm_list_hash.o	hm_vector.o	$(LIBS)




hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_vector.o: hm_vector.c hm_vector.h hm_list.h
	$(CC) hm_vector.c

hm_linklist.o: hm_linklist.c hm_linklist.h hm_pair.h
	$(CC) hm_linklist.c

hm_hash.o: hm_hash.c hm_hash.h hm_pair.h hm_vector.h
	$(CC) hm_hash.c


