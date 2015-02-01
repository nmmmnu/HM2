#ifndef _HM_DIRECTORY_H
#define _HM_DIRECTORY_H

#include "hm_file.h"


typedef struct _hm_dir_t{
	const char	*path;

	size_t		count;
	hm_file_t	*files;
} hm_dir_t;


hm_dir_t *hm_dir_open(hm_dir_t *dir, const char *path);

void hm_dir_close(hm_dir_t *dir);

const void *hm_dir_get(const hm_dir_t *dir, const char *key);

void hm_dir_printf(const hm_dir_t *dir);


#endif

