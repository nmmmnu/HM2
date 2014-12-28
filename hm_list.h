#ifndef _HM_LIST_H
#define _HM_LIST_H

#include <stdint.h>

#include "hm_pair.h"



typedef uint64_t hm_listsize_t;
typedef void hm_list_t;



hm_list_t *hm_list_create();
void hm_list_destroy(hm_list_t *v);

void hm_list_removeall(hm_list_t *v);

int hm_list_put(hm_list_t *v, hm_pair_t *newpair);

const hm_pair_t *hm_list_get(hm_list_t *v, const char *key);

int hm_list_remove(hm_list_t *v, const char *key);

hm_listsize_t hm_list_count(const hm_list_t *v);

void hm_list_dump(const hm_list_t *v);



#endif
