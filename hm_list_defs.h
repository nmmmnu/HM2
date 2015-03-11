#ifndef _hm_listdata_DEFS_H
#define _hm_listdata_DEFS_H

#include <stdio.h>	// FILE
#include <stdint.h>
#include <stdlib.h>	// size_t

#include "hm_pair.h"

int _hm_file_fwrite_junk(FILE *F, size_t count);

typedef struct _hm_fileformat_t{
	uint64_t	size;
	uint64_t	data[];
} hm_fileformat_t;

#define hm_listdata_free(a)		hm_pair_free(a)
#define hm_listdata_getkey(a)		hm_pair_getkey(a)
#define hm_listdata_valid(a, b)		hm_pair_valid(a,b)
#define hm_listdata_sizeof(a)		hm_pair_sizeof(a)
#define hm_listdata_fwrite(a, F)	hm_pair_fwrite(a, F)
#define hm_listdata_printf(a)		hm_pair_printf(a)


#endif
