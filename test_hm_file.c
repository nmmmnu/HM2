#include "hm_list.h"
#include "hm_pair.h"

#include <stdio.h>
#include <string.h>	// strlen
#include <stdlib.h>	// free
#include <ctype.h>	// isspace

#define PROCESS_STEP 1000 * 10

void processfile(hm_list_t *v, const char *filename, int op);
static char *trim(char *s);



int main(int argc, char **argv){
	const char *filename = argv[1];
	const char *findkey  = argv[2];


	hm_list_t *v = hm_list_create();


	printf("Load file\n");
	processfile(v, filename, 0);
	printf("Done...\n");



	// Find the key

	const hm_pair_t *pair = hm_list_get(v, findkey);

	if (pair == NULL)
		printf("Key %s not found\n", findkey);
	else{
		printf("Key %s found\n", findkey);

		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}


	//getchar();



	// Free list

	printf("Free file\n");
	hm_list_removeall(v);
	printf("Done...\n");

	printf("Destroy file\n");
	hm_list_destroy(v);
	printf("Done...\n");


	//getchar();


	printf("main() end...\n");

	return 0;
}

#define BUFFER_SIZE 1024

void processfile(hm_list_t *v, const char *filename, int op){
	char buffer[BUFFER_SIZE];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, BUFFER_SIZE, f)) ){
		trim(key);

		switch(op){
		case 0:
			hm_list_put(v, hm_pair_create(key, key));
			break;
		case 1:
			hm_list_remove(v, key);
			break;
		}

		i++;

		if (i % ( PROCESS_STEP ) == 0){
			printf("Processed %10u records, %10zu bytes...\n", i, hm_list_sizeof(v) );
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

