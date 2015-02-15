#ifndef _HM_VECTOR_LIST_H
#define _HM_VECTOR_LIST_H

#include "hm_vector.h"

#define hm_list_t		hm_vector_t

#define hm_list_destroy(a)	hm_vector_destroy(a)
#define hm_list_removeall(a)	hm_vector_removeall(a)

#define hm_list_put(a, data)	hm_vector_put(a, data)
#define hm_list_get(a, b)	hm_vector_get(a, b)
#define hm_list_remove(a, b)	hm_vector_remove(a, b)

#define hm_list_count(a)	hm_vector_count(a)
#define hm_list_sizeof(a)	hm_vector_sizeof(a)
#define hm_list_printf(a, b)	hm_vector_printf(a, b)

#define hm_list_fwrite(a, b)	hm_vector_fwrite(a, b)
#define hm_list_fget(a, b)	hm_vector_fget(a, b)

#endif
