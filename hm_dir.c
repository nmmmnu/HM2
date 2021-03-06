#include "hm_dir_internal.h"
#include "hm_glob.h"

#include "hm_disktable_internal.h"


#include <stdio.h>	// FILE, printf
#include <string.h>	// strdup


hm_dir_t *hm_dir_open(hm_dir_t *dir, const char *path)
{
	dir->path = path;

	glob_t globresults;

	const char **files = hm_glob_open(& globresults, dir->path);

	if (files == NULL)
		return NULL;

	size_t count = hm_glob_size(files);

	if (count == 0){
		hm_glob_close(& globresults, files);

		dir->count = 0;
		dir->files = NULL;

		// success
		return dir;
	}

	// dir->count is at least 1

	dir->files = malloc(count * sizeof(hm_disktable_t));
	if (dir->files == NULL){
		hm_glob_close(& globresults, files);

		return NULL;
	}

	dir->count = 0;

	size_t i;
	for(i = 0; i < count; ++i){
		const char *filename = files[i];
		// open the file
		hm_disktable_t *file = hm_disktable_open( & dir->files[i], filename);

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

		++(dir->count);
	}

	hm_glob_close(& globresults, files);

	return dir;
}

hm_dir_t *hm_dir_opena(const char *path)
{
	hm_dir_t *dir = malloc(sizeof(hm_dir_t));

	if (dir == NULL)
		return NULL;

	if (hm_dir_open(dir, path))
		return dir;

	free(dir);

	return NULL;
}

void hm_dir_close(hm_dir_t *dir)
{
	size_t i;
	for(i = 0; i < dir->count; ++i){
		hm_disktable_t *file = & dir->files[i];

		hm_disktable_close(file);

		// cast because file->filename is declared const
		free( (void *) file->filename );
	}

	free(dir->files);
}

hm_dir_t *hm_dir_reopen(hm_dir_t *dir)
{
	const char *path = dir->path;

	// lame - close, then open
	// however because it is read only should be quite fast.
	// also code is simpler and probably less fd's will be used
	hm_dir_close(dir);

	return hm_dir_open(dir, path);
}

const void *hm_dir_get(const hm_dir_t *dir, const char *key)
{
	size_t i;
	for(i = dir->count; i > 0; --i){
		hm_disktable_t *file = & dir->files[i - 1];

		const void *data = hm_disktable_get(file, key);

		if (data)
			return data;

		++file;
	}

	return NULL;
}

hm_dir_it_t *hm_dir_it_open(const hm_dir_t *dir)
{
	hm_dir_it_t *it = malloc(sizeof(hm_dir_it_t) + dir->count * sizeof(hm_dir_it_pair_t) );

	if (it == NULL)
		return NULL;

	it->dir = dir;
	//memset(it->p, 0, psize);

	return it;
}

void hm_dir_it_close(hm_dir_it_t *it)
{
	free(it);
}

const hm_pair_t *hm_dir_it_first(hm_dir_it_t *it)
{
	size_t i;
	for(i = 0; i < it->dir->count; ++i){
		const hm_disktable_t *file = & it->dir->files[i];

		it->p[i].pos  = 0;
		it->p[i].pair = hm_disktable_getat(file, 0);
	}

	return hm_dir_it_next(it);
}

const hm_pair_t *hm_dir_it_next(hm_dir_it_t *it)
{
	const hm_pair_t *pair = NULL;

	size_t i;

	// step 1: find minimal in reverse order to find most recent.
	for(i = it->dir->count; i > 0; --i){
		const hm_pair_t *pair2 = it->p[i - 1].pair;

		// skip pair
		if (pair2 == NULL)
			continue;

		// initialize pair
		if (pair == NULL){
			pair = pair2;
			continue;
		}

		// compare and swap pair
		if (hm_pair_cmppair(pair, pair2) > 0)
			pair = pair2;
	}

	if (pair == NULL)
		return NULL;

	// step 2: increase all duplicates
	for(i = 0; i < it->dir->count; ++i){
		const hm_pair_t *pair2 = it->p[i].pair;

		if (pair2 && hm_pair_cmppair(pair, pair2) == 0){
			const hm_disktable_t *file = & it->dir->files[i];

			it->p[i].pair = hm_disktable_getat(file, ++it->p[i].pos);
		}
	}

	return pair;
}


void hm_dir_printf(const hm_dir_t *dir)
{
	size_t i;
	for(i = 0; i < dir->count; ++i){
		hm_disktable_t *file = & dir->files[i];

		printf("%5zu : %s\n", i, file->filename);
	}
}

// ======================================================


