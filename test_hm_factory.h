#ifndef _TEST_HM_FACTORY_H
#define _TEST_HM_FACTORY_H

#include "hm_pair.h"

#define	vector_realloc_chunk_size	1024

// =======================================

#ifdef USE_VECTOR

#define HM_LIST
#include "hm_vector.h"
#undef HM_LIST

static void *_list_factory(){
	static hm_vector_t v_real;
	return hm_vector_create(& v_real, vector_realloc_chunk_size);
}

#endif

// =======================================

#ifdef USE_LINKLIST

#define HM_LIST
#include "hm_linklist.h"
#undef HM_LIST

static void *_list_factory(){
	static hm_linklist_t ll_real;
	return hm_linklist_create(& ll_real);
}

#endif

// =======================================

#ifdef USE_HASH
#include "hm_hash.h"

static hm_list_t *_list_factory(){
	static hm_hash_t ha_real;
	hm_hash_t *ha = hm_hash_create(& ha_real, 1024 * 1024, (hm_data_getkey_func_t) hm_pair_getkey, NULL, vector_realloc_chunk_size);

	return hm_hash_getlist(ha);
}

#endif

// =======================================

#endif
