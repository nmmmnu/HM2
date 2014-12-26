#ifndef _HM_LINKLIST_H
#define _HM_LINKLIST_H

#include "hm_pair.h"



typedef uint64_t linklistsize_t;

typedef struct _hm_linklist_t{
	void *head;		// system dependent
}hm_linklist_t;




hm_linklist_t *hm_linklist_create(hm_linklist_t *l);

void hm_linklist_free(hm_linklist_t *l);

int hm_linklist_put(hm_linklist_t *l, hm_pair_t *newpair);

const hm_pair_t *hm_linklist_get(hm_linklist_t *l, const char *key);

int hm_linklist_remove(hm_linklist_t *l, const char *key);

linklistsize_t hm_linklist_count(const hm_linklist_t *l);

void hm_linklist_dump(const hm_linklist_t *);



#endif

