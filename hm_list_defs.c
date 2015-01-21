#include "hm_list_defs.h"

#include "hm_pair.h"

const char *hm_list_getkey(const void *pair){
	return hm_pair_getkey( (const hm_pair_t *) pair);
}

int hm_list_valid( const void *pair1, const void *pair2){
	return hm_pair_valid( (const hm_pair_t *) pair1, (const hm_pair_t *) pair2);
}

int hm_list_fwrite(const void *pair, FILE *F){
	return hm_pair_fwrite( (const hm_pair_t *) pair, F);
}

int hm_list_printf(const void *pair){
	return hm_pair_printf( (const hm_pair_t *) pair);
}

void hm_list_free(void *item){
	hm_pair_free(item);
}
