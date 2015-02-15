CC	= gcc -Wall			\
		-g -Os			\
		-fpack-struct		\
		-D_FILE_OFFSET_BITS=64	\
		-c
LINK	= gcc -o
LIBS	=
#-ljemalloc


TARGETS =	\
		test_hm_ve test_hm_ll test_hm_ha test_hm_sl				\
		test_hm_file_ve test_hm_file_ll test_hm_file_ha	test_hm_file_sl		\
		test_hm_fwrite_ve test_hm_fwrite_ll test_hm_fwrite_ha test_hm_fwrite_sl	\
		test_hm_dir			\
		test_hm_glob


all: $(TARGETS)



clean:
	rm -f *.o $(TARGETS)



test_hm_ve:			test_hm_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o
	$(LINK) test_hm_ve	test_hm_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o					$(LIBS)

test_hm_ve.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_vector.h	hm_vector_list.h	test_hm_factory.h
	$(CC) test_hm.c -D USE_VECTOR
	mv test_hm.o test_hm_ve.o


test_hm_ll:			test_hm_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o
	$(LINK) test_hm_ll	test_hm_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o					$(LIBS)

test_hm_ll.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_linklist.h	hm_linklist_list.h	test_hm_factory.h
	$(CC) test_hm.c -D USE_LINKLIST
	mv test_hm.o test_hm_ll.o


test_hm_ha:			test_hm_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o
	$(LINK) test_hm_ha	test_hm_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o				$(LIBS)

test_hm_ha.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_hash.h	hm_hash_list.h		test_hm_factory.h	hm_vector.h
	$(CC) test_hm.c -D USE_HASH
	mv test_hm.o test_hm_ha.o

test_hm_sl:			test_hm_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o
	$(LINK) test_hm_sl	test_hm_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o					$(LIBS)

test_hm_sl.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_skiplist.h	hm_skiplist_list.h	test_hm_factory.h
	$(CC) test_hm.c -D USE_SKIPLIST
	mv test_hm.o test_hm_sl.o



test_hm_file_ve:		test_hm_file_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o
	$(LINK) test_hm_file_ve	test_hm_file_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o				$(LIBS)

test_hm_file_ve.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_vector.h	hm_vector_list.h test_hm_factory.h
	$(CC) test_hm_file.c	-D USE_VECTOR
	mv test_hm_file.o test_hm_file_ve.o


test_hm_file_ll:		test_hm_file_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o
	$(LINK) test_hm_file_ll	test_hm_file_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o				$(LIBS)

test_hm_file_ll.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_linklist.h	hm_linklist_list.h test_hm_factory.h
	$(CC) test_hm_file.c	-D USE_LINKLIST
	mv test_hm_file.o test_hm_file_ll.o


test_hm_file_ha:		test_hm_file_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o
	$(LINK) test_hm_file_ha	test_hm_file_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o			$(LIBS)

test_hm_file_ha.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_hash.h	hm_hash_list.h test_hm_factory.h hm_vector.h
	$(CC) test_hm_file.c	-D USE_HASH
	mv test_hm_file.o test_hm_file_ha.o


test_hm_file_sl:		test_hm_file_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o
	$(LINK) test_hm_file_sl	test_hm_file_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o				$(LIBS)

test_hm_file_sl.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_skiplist.h	hm_skiplist_list.h test_hm_factory.h
	$(CC) test_hm_file.c	-D USE_SKIPLIST
	mv test_hm_file.o test_hm_file_sl.o



test_hm_fwrite_ve:			test_hm_fwrite_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o hm_file.o
	$(LINK) test_hm_fwrite_ve	test_hm_fwrite_ve.o	hm_pair.o hm_list_defs.o	hm_vector.o hm_file.o		$(LIBS)

test_hm_fwrite_ve.o: test_hm_fwrite.c	hm_pair.h hm_file.h	hm_vector.h			hm_vector_list.h test_hm_factory.h
	$(CC) test_hm_fwrite.c		-D USE_VECTOR
	mv test_hm_fwrite.o test_hm_fwrite_ve.o


test_hm_fwrite_ll:			test_hm_fwrite_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o hm_file.o
	$(LINK) test_hm_fwrite_ll	test_hm_fwrite_ll.o	hm_pair.o hm_list_defs.o	hm_linklist.o hm_file.o		$(LIBS)

test_hm_fwrite_ll.o: test_hm_fwrite.c	hm_pair.h hm_file.h	hm_linklist.h			hm_linklist_list.h test_hm_factory.h
	$(CC) test_hm_fwrite.c		-D USE_LINKLIST
	mv test_hm_fwrite.o test_hm_fwrite_ll.o


test_hm_fwrite_ha:			test_hm_fwrite_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_file.o
	$(LINK) test_hm_fwrite_ha	test_hm_fwrite_ha.o	hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_file.o	$(LIBS)

test_hm_fwrite_ha.o: test_hm_fwrite.c	hm_pair.h hm_file.h	hm_vector.h hm_hash.h		hm_hash_list.h test_hm_factory.h
	$(CC) test_hm_fwrite.c		-D USE_HASH
	mv test_hm_fwrite.o test_hm_fwrite_ha.o


test_hm_fwrite_sl:			test_hm_fwrite_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o hm_file.o
	$(LINK) test_hm_fwrite_sl	test_hm_fwrite_sl.o	hm_pair.o hm_list_defs.o	hm_skiplist.o hm_file.o		$(LIBS)

test_hm_fwrite_sl.o: test_hm_fwrite.c	hm_pair.h hm_file.h	hm_skiplist.h			hm_skiplist_list.h test_hm_factory.h
	$(CC) test_hm_fwrite.c		-D USE_SKIPLIST
	mv test_hm_fwrite.o test_hm_fwrite_sl.o



test_hm_dir:			test_hm_dir.o hm_glob.o		hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_file.o hm_dir.o
	$(LINK) test_hm_dir	test_hm_dir.o hm_glob.o		hm_pair.o hm_list_defs.o	hm_hash.o hm_vector.o hm_file.o hm_dir.o	$(LIBS)

test_hm_dir.o: test_hm_dir.c		hm_pair.h hm_vector.h hm_hash.h hm_file.h
	$(CC) test_hm_dir.c



test_hm_glob:			test_hm_glob.o hm_glob.o
	$(LINK) test_hm_glob	test_hm_glob.o hm_glob.o

test_hm_glob.o: test_hm_glob.c hm_glob.h
	$(CC) test_hm_glob.c



hm_pair.h: hm_pair_inlines.h
	touch hm_pair.h

hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_list_defs.o: hm_list_defs.c hm_list_defs.h hm_pair.h
	$(CC) hm_list_defs.c

hm_vector.o: hm_vector.c hm_vector.h hm_list_defs.h
	$(CC) hm_vector.c

hm_linklist.o: hm_linklist.c hm_linklist.h hm_list_defs.h
	$(CC) hm_linklist.c

hm_skiplist.o: hm_skiplist.c hm_skiplist.h hm_list_defs.h
	$(CC) hm_skiplist.c

hm_hash.o: hm_hash.c hm_hash.h hm_pair.h hm_list_defs.h hm_vector.h
	$(CC) hm_hash.c

hm_file.o: hm_file.c hm_file.h hm_pair.h hm_list_defs.h
	$(CC) hm_file.c

hm_dir.o: hm_dir.c hm_dir.h hm_file.h
	$(CC) hm_dir.c

hm_glob.o: hm_glob.c hm_glob.h
	$(CC) hm_glob.c

