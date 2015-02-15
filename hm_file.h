#ifndef _HM_FILE_H
#define _HM_FILE_H

#include <stdio.h>	// FILE, off_t

typedef struct _hm_file_t{
	const char *filename;
	off_t size;
	FILE *F;
	char *mem;
} hm_file_t;

hm_file_t *hm_file_open(hm_file_t *mmf, const char *filename);

void hm_file_close(hm_file_t *mmf);

const void *hm_file_line_get(const hm_file_t *mmf, const char *key);
const void *hm_file_hash_get(const hm_file_t *mmf, const char *key, const unsigned long int hash);

#endif
