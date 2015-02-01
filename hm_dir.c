#include "hm_dir.h"

#include <stdio.h>	// printf
#include <string.h>	// strdup

#include <glob.h>	// glob
#include <sys/stat.h>	// stat


static int _hm_check_file(const char *filename);


hm_dir_t *hm_dir_open(hm_dir_t *dir, const char *path){
	dir->path = path;

	glob_t globresults;

	int result = glob(path, 0, NULL, & globresults);

	if (result)
		return NULL;

	size_t size = globresults.gl_pathc;

	dir->files = malloc(size * sizeof(hm_file_t));
	if (dir->files == NULL)
		return NULL;

	// check if there is something else than file / symlink in the directory
	dir->count = 0;
	size_t i;
	for (i = 0; i < globresults.gl_pathc; i++){
		const char *filename = globresults.gl_pathv[i];

		if (! _hm_check_file( filename ))
			continue;

		// open the file
		hm_file_t *file = hm_file_open(& dir->files[dir->count], filename);

		if (file == NULL){
			// this is really problematic...
			// some files are open, some are not.
			// close / free everything

			globfree(& globresults);

			// dir->count is not increased,
			// so no reason for this not to work...
			hm_dir_close(dir);

			return NULL;
		}

		// I don't like this,
		// because file->filename is "private property",
		// but it seems to be best way.
		// if fail, will produce NULL, so no checks need
		file->filename = strdup(filename);

		dir->count++;

		//printf("%5zu %s open\n", dir->count, file->filename);
	}



	globfree(& globresults);


	if (dir->count == 0){
		hm_dir_close(dir);

		return NULL;
	}


	// do realloc to save some memory
	// we do not care about errors, since original buffer is untouched.
	hm_file_t *new_files = realloc(dir->files, dir->count * sizeof(hm_file_t));

	if (new_files)
		dir->files = new_files;


	return dir;
}

void hm_dir_close(hm_dir_t *dir){
	size_t i;
	for(i = 0; i < dir->count; i++){
		hm_file_t *file = & dir->files[i];

		//printf("%5zu %s close\n", dir->count, file->filename);

		hm_file_close(file);

		// cast because file->filename is declared const
		free( (void *) file->filename );

		file++;
	}

	free(dir->files);
}

const void *hm_dir_get(const hm_dir_t *dir, const char *key){
	size_t i;
	for(i = dir->count; i > 0; i--){
		hm_file_t *file = & dir->files[i - 1];

		const void *data = hm_file_get(file, key);

		if (data)
			return data;

		file++;
	}

	return NULL;
}

void hm_dir_printf(const hm_dir_t *dir){
	size_t i;
	size_t j = 0;
	for(i = dir->count; i > 0; i--){
		hm_file_t *file = & dir->files[i - 1];

		printf("%5zu : %s\n", j++, file->filename);
	}
}


// ======================================================


static int _hm_check_file(const char *filename){
	struct stat s;
	stat(filename, & s);

	if (s.st_mode & S_IFREG)	// file
		return 1;

	if (s.st_mode & S_IFLNK)	// symlink
		return 1;

	return 0;
}
