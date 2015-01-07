#include "hm_pair.h"
#include "hm_vector.h"

#include <stdio.h>	// FILE
#include <stdlib.h>	// free

#include <endian.h>	// htobe16

hm_vector_t *getVector();

int writeVector(FILE *F, const hm_vector_t *v);

int main(int argc, char **argv){
	hm_vector_t *v = getVector();

	const char *filename = "file.bin";

	FILE *F = fopen(filename, "w");

	writeVector(F, v);

	fclose(F);

	return 0;
}

hm_vector_t *getVector(){
	static hm_vector_t v_real;
	hm_vector_t *v = hm_vector_create(& v_real, 1024, (hm_data_getkey_func_t) hm_pair_getkey, NULL);

	hm_vector_put(v, hm_pair_create("name",		"Niki"	));
	hm_vector_put(v, hm_pair_create("age",		"41"	));
	hm_vector_put(v, hm_pair_create("city",		"Sofia"	));
	hm_vector_put(v, hm_pair_create("country",	"BG"	));

	return v;
}

int writeVector(FILE *F, const hm_vector_t *v){
	uint64_t be = htobe64( (uint64_t) v->size);

	rewind(F);
	// write table size
	fwrite(& be, sizeof(uint64_t), 1, F);

	const long int table_start = ftell(F);

	// write junk table.
	be = 0x00;
	fwrite(& be, sizeof(uint64_t), v->size, F);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		// write item
		fseek(F, 0, SEEK_END);
		const uint64_t pos = ftell(F);
		be = htobe64(pos);
		hm_pair_fwrite(v->buffer[i], F);

		// write pos
		fseek(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}

