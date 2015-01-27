#include "mp_malloc.h"

#include <malloc.h>

inline static size_t _malloc_usable_size(void *p){
	return malloc_usable_size(p);
}

void *mp_malloc(mp_pool_t *pool, size_t size){
	void *p = malloc(size);

	if (p == NULL)
		return NULL;

	if (pool){
		pool->allocations++;
		pool->size += _malloc_usable_size(p);
		pool->size_total += _malloc_usable_size(p);

		if (pool->size > pool->size_max)
			pool->size_max = pool->size;
	}

	return p;
}

void mp_free(mp_pool_t *pool, void *p){
	if (pool){
		pool->deallocations--;
		pool->size -= _malloc_usable_size(p);
	}

	free(p);
}

void *mp_realloc(mp_pool_t *pool, void *p, size_t size){
	size_t oldsize = _malloc_usable_size(p);

	void *p2 = realloc(p, size);

	if (p2 == NULL)
		return NULL;

	if (pool){
		pool->reallocations++;
		pool->size = pool->size - oldsize + _malloc_usable_size(p);
		pool->size_total += _malloc_usable_size(p);

		if (pool->size > pool->size_max)
			pool->size_max = pool->size;
	}

	return p2;
}
