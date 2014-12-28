#include "hm_list.h"

#include "hm_vector.h"

#include <stdlib.h>

hm_list_t *hm_list_create(){
	hm_vector_t *v = malloc(sizeof(hm_vector_t));

	if (v == NULL)
		return NULL;

	return hm_vector_create(v, 0);
}

void hm_list_destroy(hm_list_t *v){
	hm_vector_destroy(v);
	free(v);
}

void hm_list_removeall(hm_list_t *v){
	hm_vector_removeall(v);
}

int hm_list_put(hm_list_t *v, hm_pair_t *newpair){
	return hm_vector_put(v, newpair);
}

const hm_pair_t *hm_list_get(hm_list_t *v, const char *key){
	return hm_vector_get(v, key);
}

int hm_list_remove(hm_list_t *v, const char *key){
	return hm_vector_remove(v, key);
}

hm_listsize_t hm_list_count(const hm_list_t *v){
	return hm_vector_count(v);
}

void hm_list_dump(const hm_list_t *v){
	hm_vector_dump(v);
}
