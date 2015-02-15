#ifndef _CN_MALLOC_H
#define _CN_MALLOC_H

#include <stdint.h>
#include <stdlib.h>

typedef struct _mp_pool_t{
	uint64_t	allocations;
	uint64_t	reallocations;
	uint64_t	deallocations;
	size_t		size_total;
	size_t		size;
	size_t		size_max;
}mp_pool_t;

void *mp_malloc( mp_pool_t *pool, size_t size);
void  mp_free(   mp_pool_t *pool, void *p);
void *mp_realloc(mp_pool_t *pool, void *p, size_t size);

#endif
