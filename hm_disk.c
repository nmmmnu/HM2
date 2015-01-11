#include "hm_disk.h"

#include <endian.h>	// htobe16
#include <unistd.h>	// ftruncate


static const hm_pair_t *_hm_vector_locate_pair_bsearch(const char *mem, const char *key);
static int _hm_fwrite_junk(hm_listsize_t count, FILE *F);



int hm_vector_fwrite(const hm_vector_t *v, FILE *F){
	uint64_t be;

	const uint64_t start = ftell(F);

	// write table size
	be = htobe64( (uint64_t) v->size);
	fwrite(& be, sizeof(uint64_t), 1, F);

	const uint64_t table_start = ftell(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	// using fwrite with v->size fails in some cases.
	_hm_fwrite_junk(v->size, F);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		// write item
		fseek(F, 0, SEEK_END);
		const uint64_t pos = ftell(F) - start;

		hm_pair_fwrite(v->buffer[i], F);

		// write pos
		fseek(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(pos);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}

int hm_hash_fwrite(const hm_hash_t *h, FILE *F){
	uint64_t be;

	const uint64_t start = ftell(F);

	// write table size
	be = htobe64( (uint64_t) h->capacity);
	fwrite(& be, sizeof(uint64_t), 1, F);

	const uint64_t table_start = ftell(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	// using fwrite with v->size fails in some cases.
	_hm_fwrite_junk(h->capacity, F);

	hm_capacity_t i;
	for(i = 0; i < h->capacity; i++){
		// write item
		fseek(F, 0, SEEK_END);
		const uint64_t pos = ftell(F) - start;

		hm_vector_fwrite( & h->buckets[i], F);

		// write pos
		fseek(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(pos);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}

const hm_pair_t *hm_vector_mmap(const char *mem, const char *key){
	if (key == NULL)
		return NULL;

	return _hm_vector_locate_pair_bsearch(mem, key);
}

const hm_pair_t *hm_hash_mmap(const char *mem, const char *key){
	if (key == NULL)
		return NULL;

	const uint64_t *table = (uint64_t *) mem;

	uint64_t capacity = be64toh(table[0]);

	uint64_t bucket = hm_hash_calc(key) % capacity;

	uint64_t collision_list_ptr = be64toh(table[ bucket + 1]);

	return hm_vector_mmap(& mem[collision_list_ptr], key);
}



// ==================================



static const hm_pair_t *_hm_vector_locate_pair_bsearch(const char *mem, const char *key){
	const uint64_t *table = (uint64_t *) mem;

	uint64_t start = 0;
	uint64_t end = be64toh(table[0]);

	while (start < end){
		uint64_t mid = start + ((end - start) >> 1);

		const uint64_t ptr = be64toh(table[mid + 1]);
		const hm_pair_t *pair = (hm_pair_t *) & mem[ptr];

		//printf("| %lu %lu %lu | %lu | %lx | %s\n", start, mid, end, ptr, ptr, hm_pair_getkey(pair));

		const int cmp = hm_pair_cmpkey(pair, key);

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


static int _hm_fwrite_junk(hm_listsize_t count, FILE *F){
	uint64_t be = 0xdeedbeef;

	hm_listsize_t i;
	for(i = 0; i < count; i++)
		fwrite(& be, sizeof(uint64_t), 1, F);

	return 0;
}


/*
static int _hm_fwrite_junk(hm_listsize_t count, FILE *F){
	fflush(F);

	uint64_t size = ftell(F) + sizeof(uint64_t) * count;

	ftruncate(fileno(F), size);

	return 0;
}
*/
