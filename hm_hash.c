#include "hm_hash.h"

#include "hm_vector.h"

#include <stdlib.h>
#include <string.h>	// memset
#include <inttypes.h>	// PRIu64
#include <stdio.h>



#define hash(a) hm_hash(a)
static unsigned long int hm_hash(const char *str);
static inline hm_capacity_t _hm_hash_getbucketforkey(hm_hash_t *table, const char *key);



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity){
	void *buckets = malloc(sizeof(hm_collision_list_t) * capacity);

	if (buckets == NULL)
		return NULL;

	table->capacity = capacity;
	table->buckets  = buckets;

	memset(table->buckets, 0, sizeof(hm_collision_list_t) * capacity);

	return table;
};


void hm_hash_removeall(hm_hash_t *table){
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		hm_vector_removeall( & table->buckets[i] );
}

void hm_hash_destroy(hm_hash_t *table){
	hm_hash_removeall(table);
	free(table->buckets);
}

int hm_hash_put(hm_hash_t *table, hm_pair_t *pair){
	if (pair == NULL)
		return 0;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, hm_pair_getkey(pair) );

	if (index == 0)
		return 0;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	if (hm_vector_put(bucket, pair))
		return 1;

	free(pair);

	return 0;
}

const hm_pair_t *hm_hash_get(hm_hash_t *table, const char *key){
	if (key == 0)
		return NULL;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, key );

	if (index == 0)
		return NULL;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	return hm_vector_get(bucket , key);
}

int hm_hash_remove(hm_hash_t *table, const char *key){
	if (key == NULL)
		return 0;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, key);

	if (index == 0)
		return 0;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	return hm_vector_remove(bucket, key);
}

hm_hashsize_t hm_hash_count(const hm_hash_t *table){
	hm_hashsize_t count = 0;

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		count = count + hm_vector_count( & table->buckets[i] );

	return count;
}

void hm_hash_dump(const hm_hash_t *table, int all){
	printf("HashTable @ %p\n", table);
	printf("HashTable->capacity = %" PRIu64 "\n", table->capacity);

	if (! all)
		return;

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++){
		hm_collision_list_t *v = & table->buckets[i];
		if (hm_vector_count(v)){
			printf("HashTable->buckets[%" PRIu64 "]\n", i);
			hm_vector_dump(v);
		}
	}
}

// ===============================================================

static inline hm_capacity_t _hm_hash_getbucketforkey(hm_hash_t *table, const char *key){
	if (key == NULL)
		return 0;

	return hash(key) % table->capacity + 1;
}

// DJB Hash function from CDB
static unsigned long int hm_hash(const char *str){
	// mysterious DJB const
	unsigned long hash = 5381;

	keysize_t c;
	// double () is to avoid C warning...
	while( (c = *str++) ) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

