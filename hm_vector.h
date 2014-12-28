#ifndef _HM_VECTOR_H
#define _HM_VECTOR_H

#include "hm_pair.h"



typedef uint64_t hm_vectorsize_t;

typedef struct _hm_vector_t{
	char use_linear_search;		// 1
	hm_vectorsize_t size;		// 8
	uint16_t realloc_chunk_size;	// 8
	uint64_t buffer_alloc_size;	// 8
	void **buffer;			// system dependent
}hm_vector_t;



hm_vector_t *hm_vector_create(hm_vector_t *v, uint16_t realloc_chunk_size);
void hm_vector_destroy(hm_vector_t *v);

void hm_vector_removeall(hm_vector_t *v);

int hm_vector_put(hm_vector_t *v, hm_pair_t *newpair);

const hm_pair_t *hm_vector_get(hm_vector_t *v, const char *key);

int hm_vector_remove(hm_vector_t *v, const char *key);

hm_vectorsize_t hm_vector_count(const hm_vector_t *v);

void hm_vector_dump(const hm_vector_t *v);

#endif

