#include "hm_file.h"

#include <endian.h>
#include <stdint.h>
#include <stdlib.h>	// NULL
#include <string.h>	// strcmp
#include <sys/mman.h>	// mmap

#include "hm_list_defs.h"

static const void *_hm_file_get_hashmmap(const char *mem, const char *key);
static int _hm_file_fwrite_hash(const hm_hash_t *h, FILE *F);
static int _hm_file_fwrite_vector(const hm_vector_t *v, FILE *F);


hm_file_t *hm_file_open(hm_file_t *mmf, const char *filename){
	FILE *F = fopen(filename, "r");

	if (F == NULL)
		return NULL;

	fseek(F, 0, SEEK_END);

	mmf->F = F;
	mmf->filename = filename;
	mmf->size = ftello(F);

	mmf->mem = mmap(NULL, mmf->size, PROT_READ, MAP_SHARED, fileno(mmf->F), /* offset */ 0);

	//printf("%s %llu %p\n", mmf->filename, mmf->size, mmf->mem);

	if (mmf->mem == MAP_FAILED)
		return NULL;

	return mmf;
}

void hm_file_close(hm_file_t *mmf){
	munmap(mmf->mem, mmf->size);
	fclose(mmf->F);
}

const void *hm_file_get(const hm_file_t *mmf, const char *key){
	return _hm_file_get_hashmmap(mmf->mem, key);
}

int hm_file_createfromhash(const hm_hash_t *hash, const char *filename){
	FILE *F = fopen(filename, "w");

	if (F == NULL)
		return 1;

	int res = _hm_file_fwrite_hash(hash, F);

	fclose(F);

	return res;
}

int hm_file_createfromvector(const hm_vector_t *vector, const char *filename){
	FILE *F = fopen(filename, "w");

	if (F == NULL)
		return 1;

	int res = _hm_file_fwrite_vector(vector, F);

	fclose(F);

	return res;
}


// =============================================

static const void *_hm_file_locate_bsearch(const char *mem, const char *key){
	const uint64_t *table = (uint64_t *) mem;

	uint64_t start = 0;
	uint64_t end = be64toh(table[0]);

	while (start < end){
		uint64_t mid = start + ((end - start) >> 1);

		const uint64_t ptr = be64toh(table[mid + 1]);
		const void *pair = & mem[ptr];

		//printf("| %lu %lu %lu | %lu | %lx | %s\n", start, mid, end, ptr, ptr, hm_pair_getkey(pair));

		const int cmp = strcmp(hm_listdata_getkey(pair), key);

		if (cmp == 0){
			return pair;
		}

		if (cmp < 0){
			// go right
			start = mid + 1;
		}else{
			// go left
			end = mid;
		}
	}

	return NULL;
}

inline static const void *_hm_file_get_vectormmap(const char *mem, const char *key){
	return _hm_file_locate_bsearch(mem, key);
}

static const void *_hm_file_get_hashmmap(const char *mem, const char *key){
	if (key == NULL)
		return NULL;

	const uint64_t *table = (uint64_t *) mem;

	uint64_t capacity = be64toh(table[0]);

	uint64_t bucket = hm_hash_calc(key) % capacity;

	uint64_t collision_list_ptr = be64toh(table[ bucket + 1]);

	return _hm_file_get_vectormmap(& mem[collision_list_ptr], key);
}


// =============================================


static int _hm_file_fwrite_junk(FILE *F, hm_listsize_t count){
	uint64_t be = 0xdeedbeef;

	hm_listsize_t i;
	for(i = 0; i < count; i++)
		fwrite(& be, sizeof(uint64_t), 1, F);

	return 0;
}

static int _hm_file_fwrite_vector(const hm_vector_t *v, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);

	// write table size
	be = htobe64( (uint64_t) v->size );
	fwrite(& be, sizeof(uint64_t), 1, F);

	const uint64_t table_start = ftello(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	_hm_file_fwrite_junk(F, v->size);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		// write item
		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_listdata_fwrite(v->buffer[i], F);

		// write pos
		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}

static int _hm_file_fwrite_hash(const hm_hash_t *h, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);

	// write table size
	be = htobe64( (uint64_t) h->capacity);
	fwrite(& be, sizeof(uint64_t), 1, F);

	const uint64_t table_start = ftello(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	_hm_file_fwrite_junk(F, h->capacity);

	hm_capacity_t i;
	for(i = 0; i < h->capacity; i++){
		// write item
		fseek(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		_hm_file_fwrite_vector( & h->buckets[i], F);

		// write pos
		fseek(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}
