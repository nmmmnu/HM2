#ifndef _HM_LINKLIST_H
#define _HM_LINKLIST_H


#include "hm_list.h"


typedef struct _hm_linklist_t{
	hm_data_getkey_func_t getkey;	// system dependent
	hm_data_valid_func_t valid;	// system dependent

	void *head;			// system dependent
}hm_linklist_t;


hm_linklist_t *hm_linklist_create(hm_linklist_t *l, hm_data_getkey_func_t getkey, hm_data_valid_func_t valid);

void hm_linklist_destroy(hm_linklist_t *l);

void hm_linklist_removeall(hm_linklist_t *l);

int hm_linklist_put(hm_linklist_t *l, void *data);

const void *hm_linklist_get(const hm_linklist_t *l, const char *key);

int hm_linklist_remove(hm_linklist_t *l, const char *key);

hm_listsize_t hm_linklist_count(const hm_linklist_t *l);

hm_list_t *hm_linklist_getlist(hm_linklist_t *l);

void hm_linklist_map(const hm_linklist_t *l, hm_data_map_func_t map_func);
void hm_linklist_dump(const hm_linklist_t *l);

#endif

