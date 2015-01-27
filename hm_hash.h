#ifndef _HM_HASH_H
#define _HM_HASH_H

#include "hm_list_defs.h"
#include "hm_vector.h"


typedef size_t hm_capacity_t;

typedef hm_vector_t hm_collision_list_t;



typedef struct _hm_hash_t{
	hm_capacity_t		capacity;			// system dependent

	size_t			datasize;			// system dependent
	hm_listsize_t		datacount;			// system dependent
	size_t			vector_realloc_chunk_size;	// system dependent

	hm_collision_list_t	*buckets;			// pointer to dynamic array of hm_collision_list_t with collisions
} hm_hash_t;



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity, size_t vector_realloc_chunk_size);
void hm_hash_destroy(hm_hash_t *table);

void hm_hash_removeall(hm_hash_t *table);

int hm_hash_put(hm_hash_t *table, void *data);
const void *hm_hash_get(hm_hash_t *table, const char *key);
int hm_hash_remove(hm_hash_t *table, const char *key);

inline static hm_listsize_t hm_hash_count(const hm_hash_t *table){
	return table->datacount;
}

inline static size_t hm_hash_sizeof(const hm_hash_t *table){
	return table->datasize;
}

int hm_hash_printf(const hm_hash_t *table, int more);

unsigned long int hm_hash_calc(const char *str);

#endif
