#ifndef _HM_DIRECTORY_INTERNAL_H
#define _HM_DIRECTORY_INTERNAL_H

#include "hm_dir.h"

#include "hm_disktable.h"

typedef struct _hm_dir_t{
	const char	*path;		// system depended

	size_t		count;		// system depended
	hm_disktable_t	*files;		// system depended
} hm_dir_t;

typedef struct _hm_dir_it_t{
	const hm_dir_t	*dir;		// system depended

	const size_t	count;		// system depended
	uint64_t	it[];		// 8, dynamic
} hm_dir_it_t;

#endif
