#ifndef _HM_DIRECTORY_INTERNAL_H
#define _HM_DIRECTORY_INTERNAL_H

#include "hm_dir.h"

#include "hm_disktable.h"

typedef struct _hm_dir_t{
	const char	*path;

	size_t		count;
	hm_disktable_t	*files;
} hm_dir_t;


#endif
