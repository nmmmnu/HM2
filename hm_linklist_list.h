#ifndef _HM_LINKLIST_LIST_H
#define _HM_LINKLIST_LIST_H

#include "hm_linklist.h"

#define hm_list_t		hm_linklist_t

#define hm_list_destroy(a)	hm_linklist_destroy(a)
#define hm_list_removeall(a)	hm_linklist_removeall(a)

#define hm_list_put(a, data)	hm_linklist_put(a, data)
#define hm_list_get(a, b)	hm_linklist_get(a, b)
#define hm_list_remove(a, b)	hm_linklist_remove(a, b)

#define hm_list_count(a)	hm_linklist_count(a)
#define hm_list_sizeof(a)	hm_linklist_sizeof(a)
#define hm_list_printf(a, b)	hm_linklist_printf(a, b)

#endif
