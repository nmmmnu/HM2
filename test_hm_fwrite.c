#include "hm_pair.h"
#include "hm_file.h"

#include <stdio.h>

#include <stdlib.h>	// NULL
#include <ctype.h>	// isspace

#define BUFFER_SIZE	1024
#define PROCESS_STEP	1000 * 10

#define HASHTABLE_BUCKETS	1024 * 1024


#include "test_hm_factory.h"


static char *trim(char *s);
static void loadFile(hm_list_t *list, const char *filename);


static int create_file(const char *filename_to_load, const char *filename_to_write){
	hm_list_t *list = _list_factory();

	printf("Load start..\n");

	loadFile(list, filename_to_load);

	printf("Load done..\n");
	getchar();

	printf("Save start..\n");

	FILE *F = fopen(filename_to_write, "w");
	if (F == NULL){
		printf("Can not create a file %s...\n", filename_to_write);
		return 1;
	}
	hm_list_fwrite(list, F);
	fclose(F);

	printf("Save done..\n");

	getchar();

	//hm_list_destroy(list);

	return 0;
}

static int find_in_file(const char *filename, const char *keytofind){
	hm_file_t mmf_real;

	hm_file_t *mmf = hm_file_open(&mmf_real, filename);

	if (mmf == NULL){
		printf("Can not mmap file\n");
		exit(1);
	}

#ifdef USE_HASH
	const hm_pair_t *pair = hm_file_hash_get(mmf, keytofind, _hm_hash_calc(keytofind));
#else
	const hm_pair_t *pair = hm_file_line_get(mmf, keytofind);
#endif

	if (pair){
		printf("Pair is %s\n", hm_pair_valid(pair, NULL) ? "valid" : "invalid" );
		printf("Pair checksum is %s\n", hm_pair_checksumvalid(pair) ? "valid" : "invalid" );
		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}else{
		printf("Not Found\n");
	}

	hm_file_close(mmf);

	return 0;
}

int main(int argc, char **argv){
	switch(argc){
	case 3:
		return create_file(argv[1], argv[2]);

	case 4:
		return find_in_file(argv[2], argv[3]);
	}

	printf("Usage:\n");
	printf("\t%s [txt file] [db file] - create a database\n", argv[0]);
	printf("\t%s find [db file] [key] - find in the database\n", argv[0]);

	return 1;
}



static void loadFile(hm_list_t *list, const char *filename){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		hm_list_put(list, hm_pair_create(key, NULL));

		i++;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u records, %10zu bytes...\n", i, hm_list_sizeof(list) );

		}
	}

	fclose(f);
}


static char *trim(char *s){
	char *end = s + strlen(s) - 1;
	while(end > s && isspace(*end))
		end--;

	*(end + 1) = 0;

	return s;
}

