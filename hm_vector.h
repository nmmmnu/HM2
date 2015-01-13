#ifndef _HM_VECTOR_H
#define _HM_VECTOR_H

#include "hm_list_defs.h"


typedef struct _hm_vector_t{
	hm_listsize_t size;		// 8

	size_t realloc_chunk_size;	// system dependent
	size_t buffer_alloc_size;	// system dependent

	void **buffer;			// system dependent
}hm_vector_t;


hm_vector_t *hm_vector_create(hm_vector_t *v, size_t realloc_chunk_size);

void hm_vector_destroy(hm_vector_t *v);

void hm_vector_removeall(hm_vector_t *v);

int hm_vector_put(hm_vector_t *v, void *data);

const void *hm_vector_get(const hm_vector_t *v, const char *key);

int hm_vector_remove(hm_vector_t *v, const char *key);

hm_listsize_t hm_vector_count(const hm_vector_t *v);

int hm_vector_printf(const hm_vector_t *v);

#ifdef HM_LIST
	#define hm_list_t		hm_vector_t

	#define hm_list_destroy(a)	hm_vector_destroy(a)
	#define hm_list_removeall(a)	hm_vector_removeall(a)

	#define hm_list_put(a, data)	hm_vector_put(a, data)
	#define hm_list_get(a, b)	hm_vector_get(a, b)
	#define hm_list_remove(a, b)	hm_vector_remove(a, b)

	#define hm_list_count(a)	hm_vector_count(a)
	#define hm_list_printf(a)	hm_vector_printf(a)
#endif

#endif

