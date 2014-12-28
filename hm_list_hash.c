#include "hm_list.h"

#include "hm_hash.h"

#include <stdlib.h>

hm_list_t *hm_list_create(){
	hm_hash_t *h = malloc(sizeof(hm_hash_t));

	if (h == NULL)
		return NULL;

	return hm_hash_create(h, 1024);
}

void hm_list_destroy(hm_list_t *v){
	hm_hash_destroy(v);
	free(v);
}

void hm_list_removeall(hm_list_t *v){
	hm_hash_removeall(v);
}

int hm_list_put(hm_list_t *v, hm_pair_t *newpair){
	return hm_hash_put(v, newpair);
}

const hm_pair_t *hm_list_get(hm_list_t *v, const char *key){
	return hm_hash_get(v, key);
}

int hm_list_remove(hm_list_t *v, const char *key){
	return hm_hash_remove(v, key);
}

hm_listsize_t hm_list_count(const hm_list_t *v){
	return hm_hash_count(v);
}

void hm_list_dump(const hm_list_t *v){
	hm_hash_dump(v, 1);
}
