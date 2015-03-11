#ifndef _TEST_HM_FACTORY_H
#define _TEST_HM_FACTORY_H

#include "hm_pair.h"

#include "hm_skiplist_list.h"

#define SKIPLIST_HEIGHT		32

static void *_list_factory(){
	static hm_skiplist_t ls_real;
	return hm_skiplist_create(& ls_real, SKIPLIST_HEIGHT);
}

#endif
