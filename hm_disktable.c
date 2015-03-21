#include "hm_disktable_internal.h"

#include <endian.h>
#include <stdlib.h>	// NULL
#include <string.h>	// strcmp
#include <sys/mman.h>	// mmap

#include "hm_pair.h"


inline static const void *_hm_disktable_get(const hm_disktable_t *mmf, const char *key, uint64_t *ppos);
inline static uint64_t _hm_disktable_getcount(const char *mem);

hm_disktable_t *hm_disktable_open(hm_disktable_t *mmf, const char *filename){
	FILE *F = fopen(filename, "r");

	if (F == NULL)
		return NULL;

	fseek(F, 0, SEEK_END);

	off_t size = ftello(F);

	char *mem = mmap(NULL, size, PROT_READ, MAP_SHARED, fileno(F), /* offset */ 0);

	if (mem == MAP_FAILED){
		fclose(F);
		return NULL;
	}

	//printf("%s %llu %p\n", filename, size, mem);

	mmf->F = F;
	mmf->filename = filename;
	mmf->size = size;
	mmf->mem = mem;

	// memoize count instead to read it from the disk each time
	mmf->count = _hm_disktable_getcount(mem);

	return mmf;
}

hm_disktable_t *hm_disktable_opena(const char *filename){
	hm_disktable_t *mmf = malloc(sizeof(hm_disktable_t));

	if (mmf == NULL)
		return NULL;

	if (hm_disktable_open(mmf, filename))
		return mmf;

	free(mmf);

	return NULL;
}

void hm_disktable_close(hm_disktable_t *mmf){
	munmap(mmf->mem, mmf->size);
	fclose(mmf->F);
}

off_t hm_disktable_count(const hm_disktable_t *mmf){
	return mmf->size;
}

const void *hm_disktable_get(const hm_disktable_t *mmf, const char *key){
	return _hm_disktable_get(mmf, key, NULL);
}

const void *hm_disktable_getat(const hm_disktable_t *mmf, uint64_t pos){
	if (pos >= mmf->count)
		return NULL;

	const char *mem = mmf->mem;

	const hm_disktable_fileformat_t *head = (hm_disktable_fileformat_t *) mem;

	const uint64_t ptr = be64toh( head->data[pos] );
	const void *pair = & mem[ptr];

	return pair;
}

const hm_pair_t *hm_disktable_it_first(const hm_disktable_t *mmf, hm_disktable_it_t *it){
	it->p = 0;
	return hm_disktable_it_next(mmf, it);
}

const hm_pair_t *hm_disktable_it_next(const hm_disktable_t *mmf, hm_disktable_it_t *it){
	return hm_disktable_getat(mmf, it->p++);
}

int hm_disktable_createfrommemtable(const hm_memtable_t *memtable, const char *filename_to_write){
	FILE *F = fopen(filename_to_write, "w");
	if (F == NULL){
		printf("Can not create a file %s...\n", filename_to_write);
		return 1;
	}

	int result = hm_disktable_createfrommemtablef(memtable, F);

	fclose(F);

	return result;
}

int hm_disktable_createfrommemtablef(const hm_memtable_t *memtable, FILE *F){
	uint64_t be;

	const uint64_t datacount = hm_memtable_count(memtable);
	const size_t header_size = sizeof(hm_disktable_fileformat_t);
	const size_t table_size  = sizeof(uint64_t) * datacount;

	/* preallocating the file do not really speed up the fwrite process.

	const size_t total_size  = header_size + table_size + hm_memtable_sizeof(memtable);
	posix_fallocate(fileno(F), 0, total_size);
	*/

	size_t current_place = header_size + table_size;


	// write table header (currently size only)
	hm_disktable_fileformat_t header;
	header.size = htobe64(datacount);
	fwrite(& header, sizeof(header), 1, F);

	hm_memtable_it_t it;
	const hm_pair_t *pair;

	// traverse and write the table.
	for(pair = hm_memtable_it_first(memtable, &it); pair; pair = hm_memtable_it_next(memtable, &it)){
		be = htobe64(current_place);
		fwrite(& be, sizeof(uint64_t), 1, F);

		current_place += hm_pair_sizeof(pair);
	}

	// traverse and write the data.
	for(pair = hm_memtable_it_first(memtable, &it); pair; pair = hm_memtable_it_next(memtable, &it)){
		hm_pair_fwrite(pair, F);
	}

	return 0;
}

// =============================================

static const void *_hm_disktable_locate_bsearch(const hm_disktable_t *mmf, const char *key, uint64_t *ppos){
	if (key == NULL)
		return NULL;

	uint64_t start = 0;
	uint64_t end = mmf->count;

	while (start < end){
		uint64_t mid = start + ((end - start) >> 1);

		const void *pair = hm_disktable_getat(mmf, mid);

		// This is highly unlikely, but better check it.
		if (pair == NULL)
			return NULL;

		//printf("| %lu %lu %lu | %lu | %lx | %s\n", start, mid, end, ptr, ptr, hm_pair_getkey(pair));

		const int cmp = strcmp(hm_pair_getkey(pair), key);

		if (cmp == 0){
			if (ppos)
				*ppos = mid;

			return pair;
		}

		if (cmp < 0){
			// go right
			start = mid + 1;
		}else{
			// go left
			end = mid;
		}
	}

	return NULL;
}

inline static const void *_hm_disktable_get(const hm_disktable_t *mmf, const char *key, uint64_t *ppos){
	return _hm_disktable_locate_bsearch(mmf, key, ppos);
}

inline static uint64_t _hm_disktable_getcount(const char *mem){
	const hm_disktable_fileformat_t *head = (hm_disktable_fileformat_t *) mem;
	return be64toh(head->size);
}

