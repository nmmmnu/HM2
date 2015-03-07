#ifndef _HM_FILE_H
#define _HM_FILE_H

#include <stdio.h>	// FILE, off_t
#include <stdint.h>	// uint64_t

typedef struct _hm_file_t{
	const char *filename;	// system depended
	off_t size;		// system depended, 8
	FILE *F;		// system depended
	char *mem;		// system depended
} hm_file_t;

hm_file_t *hm_file_open(hm_file_t *mmf, const char *filename);

void hm_file_close(hm_file_t *mmf);

const void *hm_file_linegetp(const hm_file_t *mmf, const char *key, uint64_t *ppos);

inline static const void *hm_file_lineget( const hm_file_t *mmf, const char *key){
	return hm_file_linegetp(mmf, key, NULL);
}

const void *hm_file_linegetat(const hm_file_t *mmf, uint64_t pos);

const void *hm_file_hashget(const hm_file_t *mmf, const char *key, const unsigned long int hash);

#endif
