#include "hm_pair.h"
#include "hm_vector.h"

#include "malloc_info.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>	// isspace



#define MAX 1024



void processfile(hm_vector_t *v, const char *filename, int op);
char *trim(char *s);



int main(int argc, char **argv){
	const char *filename = argv[1];
	const char *findkey = argv[2];

	display_mallinfo(0);

	hm_vector_t v_real;
	hm_vector_t *v = hm_vector_create(& v_real);

	printf("Load file\n");
	processfile(v, filename, 0);
	printf("Done...\n");

	const hm_pair_t *pair = hm_vector_get(v, findkey);

	if (pair == NULL)
		printf("Key %s not found\n", findkey);
	else
		printf("Key %s found - %s\n", findkey, hm_pair_getval(pair));

	display_mallinfo(0);

	getchar();

	printf("Free file\n");

	hm_vector_free(v);

	printf("Done...\n");

	display_mallinfo(0);

	getchar();

	return 0;
}

void processfile(hm_vector_t *v, const char *filename, int op){
	char buffer[MAX];

	FILE *f = fopen(filename, "r");

	unsigned int i = 0;
	char *key;
	while( (key = fgets(buffer, MAX, f)) ){
		trim(key);

		switch(op){
		case 0:
			hm_vector_put(v, hm_pair_create(key, key));
			break;
		case 1:
			hm_vector_remove(v, key);
			break;
		}

		i++;
		if (i % ( 1 * 1000 * 10 ) == 0){
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

