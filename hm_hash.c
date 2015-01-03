#include "hm_hash.h"

#include "hm_vector.h"

#include <stdlib.h>
#include <string.h>	// memset
#include <inttypes.h>	// PRIu64
#include <stdio.h>



#define hash(a) hm_hash(a)
static unsigned long int hm_hash(const char *str);
static inline hm_capacity_t _hm_hash_getbucketforkey(hm_hash_t *table, const char *key);



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity,
		hm_data_getkey_func_t getkey, hm_data_valid_func_t valid,
		size_t vector_realloc_chunk_size){
	void *buckets = malloc(sizeof(hm_collision_list_t) * capacity);

	if (buckets == NULL)
		return NULL;

	table->capacity = capacity;

	table->getkey = getkey;
	table->valid = valid;

	table->vector_realloc_chunk_size = vector_realloc_chunk_size;

	table->buckets = buckets;

	// we no longer may use simple memset()
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		hm_vector_create( & table->buckets[i], vector_realloc_chunk_size, getkey, valid);

	return table;
};

hm_list_t *hm_hash_getlist(hm_hash_t *table){
	hm_list_t *l = malloc(sizeof(hm_list_t));

	if (l == NULL)
		return l;

	l->list		= table;

	l->destroy	= (void (*)(void *))				hm_hash_destroy;
	l->removeall	= (void (*)(void *))				hm_hash_removeall;
	l->map		= (void (*)(const void *, hm_data_map_func_t))	hm_hash_map;
	l->dump		= (void (*)(const void *))			hm_hash_dump;

	l->put		= (int (*)(void *, void *))			hm_hash_put;
	l->get		= (const void *(*)(const void *, const char *))	hm_hash_get;
	l->remove	= (int (*)(void *, const char *))		hm_hash_remove;
	l->count	= (hm_listsize_t (*)(const void *))		hm_hash_count;

	return l;
}

void hm_hash_destroy(hm_hash_t *table){
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		hm_vector_destroy( & table->buckets[i] );

	free(table->buckets);
}

void hm_hash_removeall(hm_hash_t *table){
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		hm_vector_removeall( & table->buckets[i] );
}

int hm_hash_put(hm_hash_t *table, void *data){
	if (data == NULL)
		return 0;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, table->getkey(data) );

	if (index == 0)
		return 0;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	if (hm_vector_put(bucket, data))
		return 1;

	free(data);

	return 0;
}

const void *hm_hash_get(hm_hash_t *table, const char *key){
	if (key == 0)
		return NULL;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, key);

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

hm_listsize_t hm_hash_count(const hm_hash_t *table){
	hm_listsize_t count = 0;

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		count = count + hm_vector_count( & table->buckets[i] );

	return count;
}

void hm_hash_map(const hm_hash_t *table, hm_data_map_func_t map_func){
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++){
		hm_collision_list_t *v = & table->buckets[i];
		hm_vector_map(v, map_func);
	}
}

void hm_hash_dump(const hm_hash_t *table){
	printf("%s @ %p {\n", "hm_hash_t", table);

	printf("\t%-10s : %10" PRIu64 "\n", "capacity", table->capacity);

	printf("\t%-10s : [\n", "lists");
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++){
		hm_collision_list_t *v = & table->buckets[i];

		hm_vector_dump(v);

		if (i > 16){
			printf("\t\t...\n");
			break;
		}
	}
	printf("\t]\n");

	printf("}\n");
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

	size_t c;
	// double () is to avoid C warning...
	while( (c = *str++) ) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

