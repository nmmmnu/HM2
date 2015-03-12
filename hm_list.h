#ifndef _HM_SKIPLIST_LIST_H
#define _HM_SKIPLIST_LIST_H

#include "hm_skiplist.h"

#define hm_list_t		hm_skiplist_t

#define hm_list_create(a)	hm_skiplist_create(0)
#define hm_list_destroy(a)	hm_skiplist_destroy(a)
#define hm_list_removeall(a)	hm_skiplist_removeall(a)

#define hm_list_put(a, data)	hm_skiplist_put(a, data)
#define hm_list_get(a, b)	hm_skiplist_get(a, b)
#define hm_list_remove(a, b)	hm_skiplist_remove(a, b)

#define hm_list_count(a)	hm_skiplist_count(a)
#define hm_list_sizeof(a)	hm_skiplist_sizeof(a)
#define hm_list_printf(a, b)	hm_skiplist_printf(a, b)

#define hm_list_fwrite(a, b)	hm_skiplist_fwrite(a, b)
#define hm_list_fget(a, b)	hm_skiplist_fget(a, b)

#endif
