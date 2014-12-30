#ifndef _TEST_HM_FACTORY_H
#define _TEST_HM_FACTORY_H

#include "hm_list.h"

#include <stdlib.h>

// =======================================

#ifdef USE_VECTOR
#include "hm_vector.h"

static hm_list_t *_list_factory(){
	static hm_vector_t v_real;
	hm_vector_t *vp = hm_vector_create(& v_real, 1024, (hm_data_getkey_func_t) hm_pair_getkey, NULL);

	return hm_vector_getlist(vp);
}

#endif

// =======================================

#ifdef USE_LINKLIST
#include "hm_linklist.h"

static hm_list_t *_list_factory(){
	static hm_linklist_t ll_real;
	hm_linklist_t *lp = hm_linklist_create(& ll_real, (hm_data_getkey_func_t) hm_pair_getkey, NULL);

	return hm_linklist_getlist(lp);
}

#endif

// =======================================

#endif
