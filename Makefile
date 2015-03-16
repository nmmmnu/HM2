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
		test_hm test_hm_memtable test_hm_disktable		\
		test_hm_dir test_hm_glob


all: $(TARGETS)


clean:
	rm -f *.o $(TARGETS)


test_hm:				test_hm.o hm_pair.o hm_skiplist.o
	$(LINK) test_hm			test_hm.o hm_pair.o hm_skiplist.o				$(LIBS)

test_hm.o: test_hm.c hm_pair.h hm_memtable.h
	$(CC) test_hm.c


test_hm_memtable:			test_hm_memtable.o hm_pair.o hm_skiplist.o
	$(LINK) test_hm_memtable	test_hm_memtable.o hm_pair.o hm_skiplist.o			$(LIBS)

test_hm_memtable.o: test_hm_memtable.c hm_pair.h hm_memtable.h
	$(CC) test_hm_memtable.c


test_hm_disktable:			test_hm_disktable.o hm_pair.o hm_disktable.o hm_skiplist.o
	$(LINK) test_hm_disktable	test_hm_disktable.o hm_pair.o hm_disktable.o hm_skiplist.o	$(LIBS)

test_hm_disktable.o: test_hm_disktable.c hm_pair.h hm_disktable.h hm_memtable.h
	$(CC) test_hm_disktable.c



test_hm_dir:				test_hm_dir.o hm_glob.o hm_dir.o hm_pair.o hm_disktable.o hm_skiplist.o
	$(LINK) test_hm_dir		test_hm_dir.o hm_glob.o hm_dir.o hm_pair.o hm_disktable.o hm_skiplist.o	$(LIBS)

test_hm_dir.o: test_hm_dir.c hm_pair.h hm_dir.h
	$(CC) test_hm_dir.c



test_hm_glob:			test_hm_glob.o hm_glob.o
	$(LINK) test_hm_glob	test_hm_glob.o hm_glob.o

test_hm_glob.o: test_hm_glob.c hm_glob.h
	$(CC) test_hm_glob.c



hm_pair.o: hm_pair.c hm_pair.h
	$(CC) hm_pair.c



hm_skiplist.o: hm_skiplist.c hm_skiplist.h hm_skiplist_internal.h hm_pair.h hm_memtable.h
	$(CC) hm_skiplist.c

hm_disktable.o: hm_disktable.c hm_disktable.h hm_disktable_internal.h hm_pair.h hm_memtable.h
	$(CC) hm_disktable.c

hm_dir.o: hm_dir.c hm_dir.h hm_dir_internal.h hm_glob.h hm_disktable.h hm_disktable_internal.h
	$(CC) hm_dir.c

hm_glob.o: hm_glob.c hm_glob.h
	$(CC) hm_glob.c

