#ifndef _hm_hash_t_H
#define _hm_hash_t_H

#include "hm_pair.h"
#include "hm_vector.h"



typedef uint64_t hm_capacity_t;

typedef uint64_t hm_hashsize_t;

typedef hm_vector_t hm_collision_list_t;

typedef struct _hm_hash_t{
	hm_capacity_t		capacity;	// 8
	hm_collision_list_t	*buckets;	// pointer to dynamic array of hm_vector_t with collisions
} hm_hash_t;



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity);
void hm_hash_destroy(hm_hash_t *table);

void hm_hash_removeall(hm_hash_t *table);

int hm_hash_put(hm_hash_t *table, hm_pair_t *pair);
const hm_pair_t *hm_hash_get(hm_hash_t *table, const char *key);
int hm_hash_remove(hm_hash_t *table, const char *key);

hm_hashsize_t hm_hash_count(const hm_hash_t *table);

void hm_hash_dump(const hm_hash_t *table, int all);



#endif
