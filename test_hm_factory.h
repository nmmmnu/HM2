#ifndef _TEST_HM_FACTORY_H
#define _TEST_HM_FACTORY_H

#include "hm_pair.h"

#define	VECTOR_CHUNK_SIZE	1024

#ifndef HASHTABLE_BUCKETS
#define HASHTABLE_BUCKETS	16
#endif

// =======================================

#ifdef USE_VECTOR

#include "hm_vector_list.h"

static void *_list_factory(){
	static hm_vector_t v_real;
	return hm_vector_create(& v_real, VECTOR_CHUNK_SIZE);
}

#endif

// =======================================

#ifdef USE_LINKLIST

#include "hm_linklist_list.h"

static void *_list_factory(){
	static hm_linklist_t ll_real;
	return hm_linklist_create(& ll_real);
}

#endif

// =======================================

#ifdef USE_HASH

#include "hm_hash_list.h"

static void *_list_factory(){
	static hm_hash_t ha_real;
	return hm_hash_create(& ha_real, HASHTABLE_BUCKETS, VECTOR_CHUNK_SIZE);
}

#endif

// =======================================

#endif
