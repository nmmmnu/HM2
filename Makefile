MYCC	= clang
MYCC	= gcc

CC	= $(MYCC) -Wall			\
		-g -Os			\
		-D_FILE_OFFSET_BITS=64	\
		-c
LINK	= $(MYCC) -o
LIBS	=
#-ljemalloc
#-fpack-struct

TARGETS =	\
		test_hm test_hm_file test_hm_fwrite		\
		test_hm_dir test_hm_glob


all: $(TARGETS)


clean:
	rm -f *.o $(TARGETS)


test_hm:			test_hm.o	hm_pair.o hm_list_defs.o	hm_skiplist.o
	$(LINK) test_hm		test_hm.o	hm_pair.o hm_list_defs.o	hm_skiplist.o					$(LIBS)

test_hm.o:			test_hm.c	hm_pair.h hm_list_defs.h	hm_skiplist.h	hm_list.h
	$(CC) test_hm.c


test_hm_file_sl:		test_hm_file.o	hm_pair.o hm_list_defs.o	hm_skiplist.o
	$(LINK) test_hm_file_sl	test_hm_file.o	hm_pair.o hm_list_defs.o	hm_skiplist.o				$(LIBS)

test_hm_file_sl.o:		test_hm_file.c		hm_pair.h hm_list_defs.h	hm_skiplist.h	hm_list.h
	$(CC) test_hm_file.c	-D USE_SKIPLIST
	mv test_hm_file.o test_hm_file_sl.o


test_hm_fwrite:			test_hm_fwrite.o	hm_pair.o hm_list_defs.o	hm_skiplist.o hm_file.o
	$(LINK) test_hm_fwrite	test_hm_fwrite.o	hm_pair.o hm_list_defs.o	hm_skiplist.o hm_file.o		$(LIBS)

test_hm_fwrite.o: test_hm_fwrite.c	hm_pair.h hm_file.h	hm_skiplist.h		hm_list.h
	$(CC) test_hm_fwrite.c		-D USE_SKIPLIST



test_hm_dir:			test_hm_dir.o hm_glob.o		hm_pair.o hm_list_defs.o	hm_file.o hm_dir.o
	$(LINK) test_hm_dir	test_hm_dir.o hm_glob.o		hm_pair.o hm_list_defs.o	hm_file.o hm_dir.o	$(LIBS)

test_hm_dir.o: test_hm_dir.c		hm_pair.h hm_file.h
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

hm_skiplist.o: hm_skiplist.c hm_skiplist.h hm_list_defs.h
	$(CC) hm_skiplist.c

hm_file.o: hm_file.c hm_file.h hm_pair.h hm_list_defs.h
	$(CC) hm_file.c

hm_dir.o: hm_dir.c hm_dir.h hm_file.h
	$(CC) hm_dir.c

hm_glob.o: hm_glob.c hm_glob.h
	$(CC) hm_glob.c

