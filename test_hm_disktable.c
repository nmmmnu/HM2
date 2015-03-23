#include "hm_memtable.h"
#include "hm_pair.h"

#include "hm_disktable.h"

#include <stdio.h>

#include <stdlib.h>	// NULL
#include <ctype.h>	// isspace

#define BUFFER_SIZE	1024
#define PROCESS_STEP	1000 * 10

static void _load_file(hm_memtable_t *list, const char *filename);
static void _print_pair(const hm_pair_t *pair);

static int create_file(const char *filename_to_load, const char *filename_to_write){
	hm_memtable_t *list = hm_memtable_createa();


	printf("Load start..\n");

	_load_file(list, filename_to_load);

	printf("Load done..\n");
	getchar();

	printf("Save start..\n");

	hm_disktable_createfrommemtable(list, filename_to_write);

	printf("Save done..\n");

	getchar();

	hm_memtable_destroy(list);
	free(list);

	return 0;
}

static int find_in_file(const char *filename, const char *keytofind){
	hm_disktable_t *mmf = hm_disktable_opena(filename);

	if (mmf == NULL){
		printf("Can not mmap file\n");
		exit(1);
	}


	const hm_pair_t *pair = hm_disktable_get(mmf, keytofind);

	_print_pair(pair);

	hm_disktable_close(mmf);
	free(mmf);

	return 0;
}

static int dump_file(const char *filename, const char *keytofind){
	hm_disktable_t *mmf = hm_disktable_opena(filename);

	if (mmf == NULL){
		printf("Can not open file\n");
		exit(1);
	}

	hm_disktable_it_t *it = hm_disktable_it_open(mmf);
	if (it == NULL){
		printf("No memory\n");
		exit(1);
	}

	const hm_pair_t *pair;
	uint64_t i = 0;
	for(pair = hm_disktable_it_first(it); pair; pair = hm_disktable_it_next(it)){
		_print_pair(pair);

		++i;

		if (i >= 10)
			break;
	}

	hm_disktable_close(mmf);
	free(mmf);

	return 0;
}

int main(int argc, char **argv){
	if (argc > 2){
		if (argc == 4 && strcmp("make", argv[1]) == 0)
			return create_file(argv[2], argv[3]);

		if (argc == 4 && strcmp("find", argv[1]) == 0)
			return find_in_file(argv[2], argv[3]);

		if (argc == 3 && strcmp("dump", argv[1]) == 0)
			return dump_file(argv[2], NULL);

		if (argc == 4 && strcmp("dump", argv[1]) == 0)
			return dump_file(argv[2], argv[3]);
	}

	printf("Usage:\n");
	printf("\t%s make [txt file] [db file] - create a database\n", argv[0]);
	printf("\t%s find [db file] [key] - find in the database\n", argv[0]);
	printf("\t%s dump [db file] - dump the database\n", argv[0]);

	return 1;
}



static char *trim(char *s){
	char *end = s + strlen(s) - 1;
	while(end > s && isspace((unsigned char) *end))
		--end;

	*(end + 1) = 0;

	return s;
}

static void _load_file(hm_memtable_t *list, const char *filename){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		hm_memtable_put(list, hm_pair_create(key, NULL));

		++i;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u records, %10zu bytes...\n", i, hm_memtable_sizeof(list) );

		}
	}

	fclose(f);
}

static void _print_pair(const hm_pair_t *pair){
	if (pair){
		printf("Pair is %s\n", hm_pair_valid(pair, NULL) ? "valid" : "invalid" );
		printf("Pair checksum is %s\n", hm_pair_checksumvalid(pair) ? "valid" : "invalid" );
		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}else{
		printf("Not Found\n");
	}
}
