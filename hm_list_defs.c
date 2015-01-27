#include "hm_list_defs.h"

#include "hm_pair.h"

const char *hm_list_getkey(const void *pair){
	return hm_pair_getkey(pair);
}

int hm_list_valid( const void *pair1, const void *pair2){
	return hm_pair_valid(pair1, pair2);
}

int hm_list_fwrite(const void *pair, FILE *F){
	return hm_pair_fwrite(pair, F);
}

int hm_list_printf(const void *pair){
	return hm_pair_printf(pair);
}

size_t hm_list_sizeof(const void *pair){
	return hm_pair_sizeof(pair);
}

void hm_list_free(void *pair){
	hm_pair_free(pair);
}
