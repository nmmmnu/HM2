#include "hm_glob.h"

#include <sys/stat.h>	// stat


static int _hm_glob_check_file(const char *filename);

static const char **_hm_glob_emptyresult();


const char **hm_glob_open(glob_t *globresults, const char *path)
{
	int result = glob(path, 0, NULL, globresults);

	if (result == GLOB_NOMATCH)
		return _hm_glob_emptyresult();

	if (result)
		return NULL;

	// size is at least 1
	size_t size = globresults->gl_pathc;

	const char **files = malloc( (size + 1) * sizeof(char *));
	if (files == NULL)
		return NULL;

	// check if there is something else than file / symlink in the directory
	size_t j = 0;
	size_t i;
	for (i = 0; i < globresults->gl_pathc; ++i){
		const char *filename = globresults->gl_pathv[i];

		if (_hm_glob_check_file( filename ))
			files[j++] = filename;
	}

	files[j] = NULL;

	return files;
}

size_t hm_glob_size(const char **files)
{
	size_t count = 0;
	while(*files){
		++files;
		++count;
	}

	return count;
}


// ======================================================


static int _hm_glob_check_file(const char *filename)
{
	struct stat s;
	stat(filename, & s);

	if (s.st_mode & S_IFREG)	// file
		return 1;

	if (s.st_mode & S_IFLNK)	// symlink
		return 1;

	return 0;
}

static const char **_hm_glob_emptyresult()
{
	const char **m = malloc(sizeof(char *));

	if (m){
		m[0] = NULL;
		return m;
	}

	return NULL;
}

