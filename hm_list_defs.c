#include "hm_list_defs.h"

#include "hm_pair.h"

const char *hm_listdata_getkey(const void *pair){
	return hm_pair_getkey(pair);
}

int hm_listdata_valid( const void *pair1, const void *pair2){
	return hm_pair_valid(pair1, pair2);
}

int hm_listdata_fwrite(const void *pair, FILE *F){
	return hm_pair_fwrite(pair, F);
}

int hm_listdata_printf(const void *pair){
	return hm_pair_printf(pair);
}

size_t hm_listdata_sizeof(const void *pair){
	return hm_pair_sizeof(pair);
}

void hm_listdata_free(void *pair){
	hm_pair_free(pair);
}
