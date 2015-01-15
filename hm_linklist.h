#ifndef _HM_LINKLIST_H
#define _HM_LINKLIST_H


#include "hm_list_defs.h"


typedef struct _hm_linklist_t{
	void *head;			// system dependent
}hm_linklist_t;


hm_linklist_t *hm_linklist_create(hm_linklist_t *l);

void hm_linklist_destroy(hm_linklist_t *l);

void hm_linklist_removeall(hm_linklist_t *l);

int hm_linklist_put(hm_linklist_t *l, void *data);

const void *hm_linklist_get(const hm_linklist_t *l, const char *key);

int hm_linklist_remove(hm_linklist_t *l, const char *key);

hm_listsize_t hm_linklist_count(const hm_linklist_t *l);

int hm_linklist_printf(const hm_linklist_t *l, int more);

#ifdef HM_LIST
	#define hm_list_t		hm_linklist_t

	#define hm_list_destroy(a)	hm_linklist_destroy(a)
	#define hm_list_removeall(a)	hm_linklist_removeall(a)

	#define hm_list_put(a, data)	hm_linklist_put(a, data)
	#define hm_list_get(a, b)	hm_linklist_get(a, b)
	#define hm_list_remove(a, b)	hm_linklist_remove(a, b)

	#define hm_list_count(a)	hm_linklist_count(a)
	#define hm_list_printf(a, b)	hm_linklist_printf(a, b)
#endif

#endif

