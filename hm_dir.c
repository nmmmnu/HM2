#include "hm_dir.h"
#include "hm_glob.h"

#include <stdio.h>	// printf
#include <string.h>	// strdup


hm_dir_t *hm_dir_open(hm_dir_t *dir, const char *path){
	dir->path = path;

	glob_t globresults;

	const char **files = hm_glob_open(& globresults, dir->path);

	if (files == NULL)
		return NULL;

	dir->count = hm_glob_size(files);

	if (dir->count == 0){
		hm_glob_close(& globresults, files);

		dir->count = 0;
		dir->files = NULL;

		// success
		return dir;
	}

	// dir->count is at least 1

	dir->files = malloc(dir->count * sizeof(hm_file_t));
	if (dir->files == NULL)
		return NULL;

	size_t i;
	for(i = 0; i < dir->count; i++){
		const char *filename = files[i];
		// open the file
		hm_file_t *file = hm_file_open( & dir->files[i], filename);

		if (file == NULL){
			// this is really problematic...
			// some files are open, some are not.
			// close / free everything

			hm_glob_close(& globresults, files);

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
	}

	hm_glob_close(& globresults, files);

	return dir;
}

void hm_dir_close(hm_dir_t *dir){
	size_t i;
	for(i = 0; i < dir->count; i++){
		hm_file_t *file = & dir->files[i];

		hm_file_close(file);

		// cast because file->filename is declared const
		free( (void *) file->filename );
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
	for(i = 0; i < dir->count; i++){
		hm_file_t *file = & dir->files[i];

		printf("%5zu : %s\n", i, file->filename);
	}
}


// ======================================================


