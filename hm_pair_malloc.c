#include "mp_malloc/mp_malloc.h"

static mp_pool_t hm_pair_pool;
static char      hm_pair_pool_needinit = 1;

inline static void *xmalloc(size_t size){
	if (hm_pair_pool_needinit){
		memset(&hm_pair_pool, 0, sizeof(mp_pool_t));
		hm_pair_pool_needinit = 0;
	}

	return mp_malloc(&hm_pair_pool, size);
}

inline static void xfree(void *p){
	mp_free(&hm_pair_pool, p);
}

size_t hm_pair_memsize(){
	return hm_pair_pool.size;
}

