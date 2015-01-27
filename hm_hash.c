#include "hm_hash.h"

#include <stdlib.h>
#include <string.h>	// memset
//#include <inttypes.h>	// PRIu64
#include <stdio.h>



#define hash(a) hm_hash_calc(a)
static inline hm_capacity_t _hm_hash_getbucketforkey(hm_hash_t *table, const char *key);



hm_hash_t *hm_hash_create(hm_hash_t *table, hm_capacity_t capacity, size_t vector_realloc_chunk_size){
	void *buckets = malloc(sizeof(hm_collision_list_t) * capacity);

	if (buckets == NULL)
		return NULL;

	table->capacity = capacity;

	table->datasize  = 0;
	table->datacount = 0;
	table->vector_realloc_chunk_size = vector_realloc_chunk_size;

	table->buckets = buckets;

	// we no longer may use simple memset()
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		hm_vector_create( & table->buckets[i], vector_realloc_chunk_size);

	return table;
};

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

	table->datasize  = 0;
	table->datacount = 0;
}

int hm_hash_put(hm_hash_t *table, void *data){
	if (data == NULL)
		return 0;

	hm_capacity_t index = _hm_hash_getbucketforkey(table, hm_listdata_getkey(data) );

	if (index == 0)
		return 0;

	hm_collision_list_t *bucket = & table->buckets[index - 1];

	table->datacount -= hm_vector_count(bucket);
	table->datasize  -= hm_vector_sizeof(bucket);
	int result = hm_vector_put(bucket, data);
	table->datasize  += hm_vector_sizeof(bucket);
	table->datacount += hm_vector_count(bucket);

	if (result)
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

	table->datacount -= hm_vector_count(bucket);
	table->datasize  -= hm_vector_sizeof(bucket);
	int result = hm_vector_remove(bucket, key);
	table->datasize  += hm_vector_sizeof(bucket);
	table->datacount += hm_vector_count(bucket);

	return result;
}

#if 0
hm_listsize_t hm_hash_count(const hm_hash_t *table){
	hm_listsize_t count = 0;

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		count +=hm_vector_count( & table->buckets[i] );

	return count;
}

size_t hm_hash_sizeof(const hm_hash_t *table){
	size_t size = 0;

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++)
		size += hm_vector_sizeof( & table->buckets[i] );

	return size;
}
#endif

static void _hm_hash_printf_more(const hm_hash_t *table){
	printf("%s @ %p {\n", "hm_hash_t", table);

	printf("\t%-10s : %10zu\n", "capacity", table->capacity);
	printf("\t%-10s : %10zu\n", "datasize", hm_hash_sizeof(table) );

	printf("\t%-10s : [\n", "lists");
	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++){
		hm_collision_list_t *v = & table->buckets[i];

		hm_vector_printf(v, 1);

		if (i > 4){
			printf("\t\t...\n");
			break;
		}
	}
	printf("\t]\n");

	printf("}\n");
}

int hm_hash_printf(const hm_hash_t *table, int more){
	if (more)
		_hm_hash_printf_more(table);

	hm_capacity_t i;
	for(i = 0; i < table->capacity; i++){
		hm_collision_list_t *v = & table->buckets[i];

		printf("Bucket # %2zu:\n", i);

		hm_vector_printf(v, 0);

		if (i > 16){
			printf("...\n");
			break;
		}
	}

	return 0;
}

// DJB Hash function from CDB
unsigned long int hm_hash_calc(const char *str){
	// mysterious DJB const
	unsigned long hash = 5381;

	size_t c;
	// double () is to avoid C warning...
	while( (c = *str++) ) {
		hash = ((hash << 5) + hash) + c;
	}

	return hash;
}

// ===============================================================

static inline hm_capacity_t _hm_hash_getbucketforkey(hm_hash_t *table, const char *key){
	if (key == NULL)
		return 0;

	/*
	Instead of modulo, this can be done with bit AND.
	Doing so, really increase the speed a bit,
	but code for file based operations get more complicated,
	and overal result will be low quality code.
	*/

	return hash(key) % table->capacity + 1;
}

