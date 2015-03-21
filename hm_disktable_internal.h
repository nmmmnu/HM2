#ifndef _HM_DISKTABLE_INTERNAL_H
#define _HM_DISKTABLE_INTERNAL_H

#include "hm_disktable.h"

typedef struct _hm_disktable_t{
	const char *filename;	// system depended
	off_t size;		// system depended, 8
	FILE *F;		// system depended
	uint64_t count;		// 8
	char *mem;		// system depended
} hm_disktable_t;


typedef struct _hm_disktable_fileformat_t{
	uint64_t	size;
	uint64_t	data[];
} __attribute__((__packed__)) hm_disktable_fileformat_t;
// yes, we *want* __attribute__ to give error on no-GCC

#endif
