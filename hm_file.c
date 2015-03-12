#include "hm_file.h"

#include <endian.h>
#include <stdlib.h>	// NULL
#include <string.h>	// strcmp
#include <sys/mman.h>	// mmap

#include "hm_list_defs.h"
#include "hm_pair.h"

inline static const void *_hm_file_lineget(const char *mem, const char *key, uint64_t *ppos);

hm_file_t *hm_file_open(hm_file_t *mmf, const char *filename){
	FILE *F = fopen(filename, "r");

	if (F == NULL)
		return NULL;

	fseek(F, 0, SEEK_END);

	mmf->F = F;
	mmf->filename = filename;
	mmf->size = ftello(F);

	mmf->mem = mmap(NULL, mmf->size, PROT_READ, MAP_SHARED, fileno(mmf->F), /* offset */ 0);

	//printf("%s %llu %p\n", mmf->filename, mmf->size, mmf->mem);

	if (mmf->mem == MAP_FAILED)
		return NULL;

	return mmf;
}

void hm_file_close(hm_file_t *mmf){
	munmap(mmf->mem, mmf->size);
	fclose(mmf->F);
}

const void *hm_file_linegetp(const hm_file_t *mmf, const char *key, uint64_t *ppos){
	if (key == NULL)
		return NULL;

	return _hm_file_lineget(mmf->mem, key, ppos);
}

const void *hm_file_linegetat(const hm_file_t *mmf, uint64_t pos){
	const char *mem = mmf->mem;

	const hm_fileformat_t *head = (hm_fileformat_t *) mem;
	uint64_t end = be64toh(head->size);

	if (pos >= end)
		return NULL;

	const uint64_t ptr = be64toh( head->data[pos] );
	const void *pair = & mem[ptr];

	return pair;
}

// =============================================

static const void *_hm_file_locate_bsearch(const char *mem, const char *key, uint64_t *ppos){
	const hm_fileformat_t *head = (hm_fileformat_t *) mem;

	uint64_t start = 0;
	uint64_t end = be64toh(head->size);

	while (start < end){
		uint64_t mid = start + ((end - start) >> 1);

		const uint64_t ptr = be64toh( head->data[mid] );
		const void *pair = & mem[ptr];

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

inline static const void *_hm_file_lineget(const char *mem, const char *key, uint64_t *ppos){
	return _hm_file_locate_bsearch(mem, key, ppos);
}

