#ifndef _HM_LINKLIST_H
#define _HM_LINKLIST_H


#include "hm_list_defs.h"


typedef struct _hm_linklist_t{
	size_t	datasize;	// system dependent
	void	*head;		// system dependent
}hm_linklist_t;


hm_linklist_t *hm_linklist_create(hm_linklist_t *l);

void hm_linklist_destroy(hm_linklist_t *l);

void hm_linklist_removeall(hm_linklist_t *l);

int hm_linklist_put(hm_linklist_t *l, void *data);

const void *hm_linklist_get(const hm_linklist_t *l, const char *key);

int hm_linklist_remove(hm_linklist_t *l, const char *key);

hm_listsize_t hm_linklist_count(const hm_linklist_t *l);

inline static size_t hm_linklist_sizeof(const hm_linklist_t *l){
	return l->datasize;
}

int hm_linklist_printf(const hm_linklist_t *l, int more);

#endif

