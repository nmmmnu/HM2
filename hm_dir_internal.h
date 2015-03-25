#ifndef _HM_DIRECTORY_INTERNAL_H
#define _HM_DIRECTORY_INTERNAL_H

#include "hm_dir.h"

#include "hm_disktable.h"

typedef struct _hm_dir_t{
	const char		*path;		// system depended

	size_t			count;		// system depended
	hm_disktable_t		*files;		// system depended
} hm_dir_t;

typedef struct _hm_dir_it_pair_t{
	uint64_t		pos;		// 8
	const hm_pair_t		*pair;		// system depended
} hm_dir_it_pair_t;				// 16?

typedef struct _hm_dir_it_t{
	const hm_dir_t		*dir;		// system depended

	hm_dir_it_pair_t	p[];		// 16?, dynamic
} hm_dir_it_t;

#endif
