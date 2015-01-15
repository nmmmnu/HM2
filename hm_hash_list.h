#ifndef _HM_HASH_LIST_H
#define _HM_HASH_LIST_H

#include "hm_hash.h"

#define hm_list_t		hm_hash_t

#define hm_list_destroy(a)	hm_hash_destroy(a)
#define hm_list_removeall(a)	hm_hash_removeall(a)

#define hm_list_put(a, data)	hm_hash_put(a, data)
#define hm_list_get(a, b)	hm_hash_get(a, b)
#define hm_list_remove(a, b)	hm_hash_remove(a, b)

#define hm_list_count(a)	hm_hash_count(a)
#define hm_list_printf(a, b)	hm_hash_printf(a, b)

#endif

