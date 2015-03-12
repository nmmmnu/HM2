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


#endif
