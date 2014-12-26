#include "hm_list.h"

#include "hm_linklist.h"

#include <stdlib.h>

hm_list_t *hm_list_create(){
	hm_linklist_t *v = malloc(sizeof(hm_linklist_t));

	if (v == NULL)
		return NULL;

	return hm_linklist_create(v);
}

void hm_list_free(hm_list_t *v){
	hm_linklist_free(v);
}

int hm_list_put(hm_list_t *v, hm_pair_t *newpair){
	return hm_linklist_put(v, newpair);
}

const hm_pair_t *hm_list_get(hm_list_t *v, const char *key){
	return hm_linklist_get(v, key);
}

int hm_list_remove(hm_list_t *v, const char *key){
	return hm_linklist_remove(v, key);
}

hm_listsize_t hm_list_count(const hm_list_t *v){
	return hm_linklist_count(v);
}

void hm_list_dump(const hm_list_t *v){
	hm_linklist_dump(v);
}
