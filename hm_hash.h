#ifndef _hm_hash_t_H
#define _hm_hash_t_H

#include "hm_list.h"
#include "hm_vector.h"

typedef uint64_t hm_capacity_t;


typedef hm_vector_t hm_collision_list_t;

typedef struct _hm_hash_t{
	hm_capacity_t		capacity;	// 8

	hm_data_getkey_func_t 	getkey;		// system dependent
	hm_data_valid_func_t	valid;		// system dependent

	size_t			vector_realloc_chunk_size;	// system dependent

	hm_collision_list_t	*buckets;	// pointer to dynamic array of hm_collision_list_t with collisions
} hm_hash_t;



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity,
		hm_data_getkey_func_t getkey, hm_data_valid_func_t valid,
		size_t vector_realloc_chunk_size);
void hm_hash_destroy(hm_hash_t *table);

void hm_hash_removeall(hm_hash_t *table);

int hm_hash_put(hm_hash_t *table, void *data);
const void *hm_hash_get(hm_hash_t *table, const char *key);
int hm_hash_remove(hm_hash_t *table, const char *key);

hm_listsize_t hm_hash_count(const hm_hash_t *table);

hm_list_t *hm_hash_getlist(hm_hash_t *table);

void hm_hash_map(const hm_hash_t *table, hm_data_map_func_t map_func);
void hm_hash_dump(const hm_hash_t *table);

#endif
