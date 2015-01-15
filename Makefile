CC	= gcc -Wall			\
		-g -O0			\
		-fpack-struct		\
		-D_FILE_OFFSET_BITS=64	\
		-c
LINK	= gcc -o
LIBS	=
#-ljemalloc

TARGETS = 	\
		test_hm_ve test_hm_ll test_hm_ha		\
		test_hm_file_ve test_hm_file_ll test_hm_file_ha	\
		test_hm_fwrite

TARGETS =	\
		test_hm_ve test_hm_ll test_hm_ha		\
		test_hm_file_ve test_hm_file_ll test_hm_file_ha	\
		test_hm_fwrite


all: $(TARGETS)



clean:
	rm -f *.o $(TARGETS)



test_hm_ve:			test_hm_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o
	$(LINK) test_hm_ve	test_hm_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o			$(LIBS)

test_hm_ve.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_vector.h	hm_vector_list.h	test_hm_factory.h
	$(CC) test_hm.c -D USE_VECTOR
	mv test_hm.o test_hm_ve.o


test_hm_ll:			test_hm_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o
	$(LINK) test_hm_ll	test_hm_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o			$(LIBS)

test_hm_ll.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_linklist.h	hm_linklist_list.h	test_hm_factory.h
	$(CC) test_hm.c -D USE_LINKLIST
	mv test_hm.o test_hm_ll.o


test_hm_ha:			test_hm_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o
	$(LINK) test_hm_ha	test_hm_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o		$(LIBS)

test_hm_ha.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_hash.h	hm_hash_list.h		test_hm_factory.h	hm_vector.h
	$(CC) test_hm.c -D USE_HASH
	mv test_hm.o test_hm_ha.o



test_hm_file_ve:		test_hm_file_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o
	$(LINK) test_hm_file_ve	test_hm_file_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o		$(LIBS)

test_hm_file_ve.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_vector.h	hm_vector_list.h test_hm_factory.h
	$(CC) test_hm_file.c	-D USE_VECTOR
	mv test_hm_file.o test_hm_file_ve.o


test_hm_file_ll:		test_hm_file_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o
	$(LINK) test_hm_file_ll	test_hm_file_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o		$(LIBS)

test_hm_file_ll.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_linklist.h	hm_linklist_list.h test_hm_factory.h	
	$(CC) test_hm_file.c	-D USE_LINKLIST
	mv test_hm_file.o test_hm_file_ll.o


test_hm_file_ha:		test_hm_file_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o
	$(LINK) test_hm_file_ha	test_hm_file_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o	$(LIBS)

test_hm_file_ha.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_hash.h	hm_hash_list.h test_hm_factory.h hm_vector.h
	$(CC) test_hm_file.c	-D USE_HASH
	mv test_hm_file.o test_hm_file_ha.o



test_hm_fwrite:			test_hm_fwrite.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_disk.o
	$(LINK) test_hm_fwrite	test_hm_fwrite.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_disk.o	$(LIBS)

test_hm_fwrite.o: test_hm_fwrite.c	hm_pair.h hm_vector.h hm_hash.h hm_disk.h
	$(CC) test_hm_fwrite.c



hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_list_defs.o: hm_list_defs.c hm_list_defs.h
	$(CC) hm_list_defs.c

hm_vector.o: hm_vector.c hm_vector.h hm_list_defs.h
	$(CC) hm_vector.c

hm_linklist.o: hm_linklist.c hm_linklist.h hm_list_defs.h
	$(CC) hm_linklist.c

hm_hash.o: hm_hash.c hm_hash.h hm_pair.h hm_list_defs.h hm_vector.h
	$(CC) hm_hash.c

hm_disk.o: hm_disk.c hm_disk.h hm_vector.h hm_pair.h
	$(CC) hm_disk.c

