#include "hm_memtable.h"
#include "hm_pair.h"

#include <stdio.h>
#include <string.h>	// strlen
#include <stdlib.h>	// free
#include <ctype.h>	// isspace

#define PROCESS_STEP 1000 * 10

static void _loadfile(hm_memtable_t *v, const char *filename, int op);
static void _findkey(hm_memtable_t *v, const char *key);
static char *trim(char *s);



int main(int argc, char **argv){
	if (argc < 2){
		printf("Usage:\n");
		printf("\t%s filename [key to find]\n", argv[0]);
		exit(1);
	}

	const char *filename = argv[1];


	hm_memtable_t *v = hm_memtable_createa();


	printf("Load file\n");
	_loadfile(v, filename, 0);
	printf("Done...\n");


	if (argc > 2){
		// Find the key
		const char *findkey = argv[2];
		_findkey(v, findkey);
	}


	//getchar();


	// Free list

	printf("Free file\n");
	hm_memtable_removeall(v);
	printf("Done...\n");

	printf("Destroy file\n");
	hm_memtable_destroy(v);
	free(v);
	printf("Done...\n");


	//getchar();


	printf("main() end...\n");

	return 0;
}

#define BUFFER_SIZE 1024

static void _loadfile(hm_memtable_t *v, const char *filename, int op){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		switch(op){
		case 0:
			hm_memtable_put(v, hm_pair_create(key, key));
			break;
		case 1:
			hm_memtable_remove(v, key);
			break;
		}

		i++;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u records, %10zu bytes...\n", i, hm_memtable_sizeof(v) );
		}
	}

	fclose(f);
}

static void _findkey(hm_memtable_t *v, const char *findkey){
	const hm_pair_t *pair = hm_memtable_get(v, findkey);

	if (pair == NULL){
		printf("Key %s not found\n", findkey);
	}else{
		printf("Key %s found\n", findkey);

		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}
}


static char *trim(char *s){
	char *end = s + strlen(s) - 1;
	while(end > s && isspace((unsigned char) *end))
		end--;

	*(end + 1) = 0;

	return s;
}

