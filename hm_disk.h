#ifndef _HM_DISK_H
#define _HM_DISK_H

#include <stdio.h>	// FILE

#include "hm_hash.h"
#include "hm_vector.h"
#include "hm_pair.h"


int hm_hash_fwrite(const hm_hash_t *h, FILE *f);
int hm_vector_fwrite(const hm_vector_t *v, FILE *f);

const hm_pair_t *hm_vector_mmap(const char *mem, const char *key);
const hm_pair_t *hm_hash_mmap(const char *mem, const char *key);


#endif
