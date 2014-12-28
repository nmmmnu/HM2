#include "hm_pair.h"
#include "hm_list.h"

#include <stdio.h>
#include <string.h>	// strlen
#include <stdlib.h>	// free
#include <ctype.h>	// isspace

#define PROCESS_STEP 1000 * 10

void processfile(hm_list_t *v, const char *filename, int op);
char *trim(char *s);



int main(int argc, char **argv){
	const char *filename = argv[1];
	const char *findkey  = argv[2];



	// Create and load

	hm_list_t *v = hm_list_create();

	printf("Load file\n");
	processfile(v, filename, 0);
	printf("Done...\n");



	// Find the key

	const hm_pair_t *pair = hm_list_get(v, findkey);

	if (pair == NULL)
		printf("Key %s not found\n", findkey);
	else
		printf("Key %s found - %s\n", findkey, hm_pair_getval(pair));



	//getchar();



	// Free list

	printf("Free file\n");
	hm_list_removeall(v);
	printf("Done...\n");

	hm_list_destroy(v);



	//getchar();



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
			printf("Processed %10u...\n", i);
		}
	}

	fclose(f);
}


char *trim(char *s){
	size_t i;
	for(i = strlen(s); i > 0; i--)
		if (isspace((int) s[i]) || s[i] == '\0')
			s[i] = '\0';
		else
			break;

	return s;
}

