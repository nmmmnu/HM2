#ifndef _HM_GLOB_H
#define _HM_GLOB_H

#include <glob.h>	// glob
#include <stdlib.h>	// malloc, free, NULL

const char **hm_glob_open(glob_t *globresults, const char *path);

size_t hm_glob_size(const char **files);

inline static void hm_glob_close(glob_t *globresults, const char **files){
	free(files);
	globfree(globresults);
}

#endif

