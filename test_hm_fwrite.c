#include "hm_pair.h"
#include "hm_file.h"

#include <stdio.h>

#include <stdlib.h>	// NULL
#include <ctype.h>	// isspace




#define BUFFER_SIZE	1024
#define PROCESS_STEP	1000 * 10

#define HASH_BUCKETS	1024 * 1024
#define VECTOR_CHUNK	1 * sizeof(void *)


int hm_hash_fwrite(const hm_hash_t *h, FILE *F);


static char *trim(char *s);
static void loadFile(hm_hash_t *h, const char *filename);


static int create_file(const char *filename_to_load, const char *filename_to_write){
	static hm_hash_t h_real;
	hm_hash_t *h = hm_hash_create(& h_real, HASH_BUCKETS, VECTOR_CHUNK);

	printf("Load start..\n");

	loadFile(h, filename_to_load);

	printf("Load done..\n");
	getchar();

	printf("Save start..\n");

	hm_file_createfromhash(h, filename_to_write);

	printf("Save done..\n");
	getchar();

	return 0;
}


static int find_in_file(const char *filename, const char *keytofind){
	hm_file_t mmf_real;

	hm_file_t *mmf = hm_file_open(&mmf_real, filename);

	if (mmf == NULL){
		printf("Can not mmap file\n");
		exit(1);
	}

	const hm_pair_t *pair = hm_file_get(mmf, keytofind);

	if (pair){
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



static void loadFile(hm_hash_t *h, const char *filename){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		hm_hash_put(h, hm_pair_create(key, NULL));

		i++;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u...\n", i);
		}
	}

	fclose(f);
}


static char *trim(char *s){
	size_t i;
	for(i = strlen(s); i > 0; i--)
		if (isspace((int) s[i]) || s[i] == '\0')
			s[i] = '\0';
		else
			break;

	return s;
}

