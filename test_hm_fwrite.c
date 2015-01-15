#include "hm_pair.h"
#include "hm_disk.h"

#include <stdio.h>
#include <inttypes.h>	// PRIu64

#include <stdlib.h>	// free
#include <ctype.h>	// isspace
//#include <endian.h>	// htobe16

#include <fcntl.h>	// open
#include <unistd.h>	// close
#include <sys/mman.h>	// mmap
#include <sys/stat.h>	// stat

#define BUFFER_SIZE	1024
#define PROCESS_STEP	1000 * 10

#define HASH_BUCKETS	4
//1024 * 1024
#define VECTOR_CHUNK	1024


static char *trim(char *s);
static void loadFile(hm_hash_t *h, const char *filename);
static void writeFile(hm_hash_t *h, const char *filename);

int create_file(const char *filename_to_load, const char *filename_to_write){
	static hm_hash_t h_real;
	hm_hash_t *h = hm_hash_create(& h_real, HASH_BUCKETS, VECTOR_CHUNK);

	printf("Load start..\n");

	loadFile(h, filename_to_load);

	printf("Load done..\n");
	getchar();

	printf("Save start..\n");

	writeFile(h, filename_to_write);

	printf("Save done..\n");
	getchar();

	return 0;
}

int find_in_file(const char *filename, const char *keytofind){
	FILE *F = fopen(filename, "r");

	fseek(F, 0, SEEK_END);
	
	const uint64_t size = ftello(F);

	int fd = fileno(F);

	printf("File: %s (%d) is %" PRIu64 " bytes...\n", filename, fd, size);

	char *m = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, /* offset */ 0);

	if (m == MAP_FAILED){
		printf("MMAP failed...\n");
		exit(1);
	}

	const hm_pair_t *pair = hm_hash_mmap(m, keytofind);

	if (pair){
		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}else{
		printf("Not Found\n");
	}

	fclose(F);

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

static void writeFile(hm_hash_t *h, const char *filename){
	FILE *F = fopen(filename, "w");

	hm_hash_fwrite(h, F);

	fclose(F);
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

