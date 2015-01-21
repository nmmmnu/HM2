#ifndef _HM_FILE_H
#define _HM_FILE_H

#include <stdio.h>	// FILE, off_t

#include "hm_hash.h"	// hm_hash_calc

typedef struct _hm_file_t{
	const char *filename;
	off_t size;
	FILE *F;
	char *mem;
} hm_file_t;

hm_file_t *hm_file_open(hm_file_t *mmf, const char *filename);

void hm_file_close(hm_file_t *mmf);

const void *hm_file_get(const hm_file_t *mmf, const char *key);

int hm_file_createfromhash(const hm_hash_t *hash, const char *filename);
int hm_file_createfromvector(const hm_vector_t *vector, const char *filename);

#endif
