#include "hm_pair.h"
#include "hm_disk.h"

#include <stdio.h>
#include <stdlib.h>	// free
#include <ctype.h>	// isspace
#include <endian.h>	// htobe16

#include <fcntl.h>	// open
#include <unistd.h>	// close
#include <sys/mman.h>	// mmap

#define BUFFER_SIZE 1024
#define PROCESS_STEP 1000 * 10


static char *trim(char *s);
static void loadFile(hm_hash_t *h, const char *filename);
static void writeFile(hm_hash_t *h, const char *filename);


int main(int argc, char **argv){
	const char *filename = argv[2];

	if (0){
		static hm_hash_t h_real;
		hm_hash_t *h = hm_hash_create(& h_real, 1024 * 1024, (hm_data_getkey_func_t) hm_pair_getkey, NULL, 1024);

		printf("Load start..\n");

		loadFile(h, argv[1]);

		printf("Load done..\n");
		getchar();

		printf("Save start..\n");

		writeFile(h, filename);

		printf("Save done..\n");
		getchar();

		exit(0);
	}

	const char *keytofind = argv[3];

	int fd = open(filename, O_RDONLY);
	char *m = mmap(NULL, (size_t) 1024 * 1024 * 1024 * 10, PROT_READ, MAP_SHARED, fd, /* offset */ 0);

	if (m == MAP_FAILED){
		printf("MMAP failed...\n");
		exit(1);
	}

	const hm_pair_t *pair = hm_hash_mmap(m, keytofind);

	if (pair){
		hm_pair_dump(pair);
	}else{
		printf("Not Found\n");
	}

	return 0;
}

static void writeFile(hm_hash_t *h, const char *filename){
	int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

	hm_hash_fwrite(h, fd);

	close(fd);
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

