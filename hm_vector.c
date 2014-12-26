#include <stdint.h>
#include <stdlib.h>
#include <string.h>	// memmove
#include <stdio.h>
#include <inttypes.h>	// PRIu64

#include "hm_vector.h"



#define USE_BINSEARCH	1

#define REALLOC_CHUNK_SIZE 1024

#define DUMP_FORMAT "%5" PRIu64 " : %-10s : %-20s\n"



static hm_vector_t *_hm_vector_clear(hm_vector_t *v);
static int _hm_vector_locate_position(hm_vector_t *v, const char *key, hm_vectorsize_t *index);
static int _hm_vector_shiftL(hm_vector_t *v, hm_vectorsize_t index);
static int _hm_vector_shiftR(hm_vector_t *v, hm_vectorsize_t index);



hm_vector_t *hm_vector_create(hm_vector_t *v){
	return _hm_vector_clear(v);
}

void hm_vector_free(hm_vector_t *v){
	if (v->buffer)
		free(v->buffer);

	_hm_vector_clear(v);
}

int hm_vector_put(hm_vector_t *v, hm_pair_t *newpair){
	const char *key = hm_pair_getkey(newpair);

	hm_vectorsize_t index;
	int cmp = _hm_vector_locate_position(v, key, & index);

	if (cmp == 0){
		// key exists, overwrite, do not shift

		hm_pair_t *pair = v->buffer[index];

		// check if the data in database is newer than "newpair"
		if (pair->created > newpair->created){
			// prevent memory leak
			free(newpair);
			return 0;
		}

		free(pair);
		v->buffer[index] = newpair;
		return 1;
	}

	if ( ! _hm_vector_shiftR(v, index) )
		return 0;


	v->buffer[index] = newpair;
	return 1;
}

const hm_pair_t *hm_vector_get(hm_vector_t *v, const char *key){
	hm_vectorsize_t index;
	if (_hm_vector_locate_position(v, key, & index) == 0){
		hm_pair_t *pair = v->buffer[index];

		return hm_pair_valid(pair) ? pair : NULL;
	}

	return NULL;
}

int hm_vector_remove(hm_vector_t *v, const char *key){
	hm_vectorsize_t index;
	int cmp = _hm_vector_locate_position(v, key, & index);

	if (cmp){
		// the key does not exists in the vector.
		return 1;
	}

	// proceed with remove
	free(v->buffer[index]);

	_hm_vector_shiftL(v, index);

	return 1;
}

hm_vectorsize_t hm_vector_count(const hm_vector_t *v){
	return v->size;
}

void hm_vector_dump(const hm_vector_t *v){
	printf("Vector @ %p\n", v);

	printf("Vector->size = %" PRIu64 "\n", v->size);

	hm_vectorsize_t i;
	for(i = 0; i < v->size; i++){
		const hm_pair_t *pair = v->buffer[i];
		printf(DUMP_FORMAT, i, hm_pair_getkey(pair), hm_pair_getval(pair));
	}
}

// ===============================================================

static hm_vector_t *_hm_vector_clear(hm_vector_t *v){
	v->size = 0;
	v->buffer_alloc_size = 0;
	v->buffer = NULL;

	return v;
}

static uint64_t _hm_vector_calcnewsize(uint64_t size){
	uint32_t newsize = size / REALLOC_CHUNK_SIZE;
	if (size % REALLOC_CHUNK_SIZE)
		newsize++;

	return newsize * REALLOC_CHUNK_SIZE;
}

static int _hm_vector_resize(hm_vector_t *v, int delta){
	if (delta == 0){
		// already resized, done :)
		return 1;
	}

	if (delta > 1)
		delta = 1;

	if (delta < -1)
		delta = -1;

	hm_vectorsize_t new_size = v->size + delta;

	if (new_size == 0){
		hm_vector_free(v);
		return 1;
	}

	uint64_t new_buffer_alloc_size = _hm_vector_calcnewsize(new_size * sizeof(void *));

	void *new_buffer = realloc(v->buffer, new_buffer_alloc_size);

	if (new_buffer == NULL)
		return 0;

	v->size			= new_size;
	v->buffer_alloc_size	= new_buffer_alloc_size;
	v->buffer		= new_buffer;

	return 1;
}

#ifndef USE_BINSEARCH

static int _hm_vector_locate_position_dumb(hm_vector_t *v, const char *key, hm_vectorsize_t *index){
	// dumb - visit every node
	hm_vectorsize_t i;
	for(i = 0; i < v->size; i++){
		const hm_pair_t *pair = v->buffer[i];
		const int cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0){
			*index = i;
			return 0;
		}

		if (cmp > 0){
			*index = i;
			return 1;
		}
	}

	*index = i;
	return -1;
}

#else

static int _hm_vector_locate_position_bsearch(hm_vector_t *v, const char *key, hm_vectorsize_t *index){

	/*
	 * Lazy based from Linux kernel...
	 * http://lxr.free-electrons.com/source/lib/bsearch.c
	 */

	hm_vectorsize_t start = 0;
	hm_vectorsize_t end = v->size;
	int cmp;

	while (start < end){
		hm_vectorsize_t mid = start + (end - start) / 2;

		const hm_pair_t *pair = v->buffer[mid];

		cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0){
			*index = mid;
			return 0;
		}

		if (cmp < 0){
			// go right
			start = mid + 1;
		}else{
			// go left
			end = mid;
		}
	}

	#ifdef _test
		printf("---begin-----------\n");
		hm_vector_dump(v);
		printf("%u %lu %lu %lu (%d) %s\n", 0, start, end, v->size, cmp, key);
		printf("---end-------------\n");
	#endif

	*index = start;
	return cmp;
}

#endif

static int _hm_vector_locate_position(hm_vector_t *v, const char *key, hm_vectorsize_t *index){
	if (v->size == 0){
		*index = 0;
		return 1;
	}

#ifndef USE_BINSEARCH
	return _hm_vector_locate_position_dumb(v, key, index);
#else
	return _hm_vector_locate_position_bsearch(v, key, index);
#endif

}

static int _hm_vector_shiftR(hm_vector_t *v, hm_vectorsize_t index){
	if (! _hm_vector_resize(v, 1))
		return 0;

	// this is the most slow operation of them all
	memmove(& v->buffer[index + 1], & v->buffer[index], (v->size - index - 1) * sizeof(void *));

	return 1;
}

static int _hm_vector_shiftL(hm_vector_t *v, hm_vectorsize_t index){
	// this is the most slow operation of them all
	memmove(& v->buffer[index], & v->buffer[index + 1], (v->size - index) * sizeof(void *));

	_hm_vector_resize(v, -1);

	return 1;
}


