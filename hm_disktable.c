#include "hm_disktable_internal.h"

#include <endian.h>
#include <stdlib.h>	// NULL
#include <string.h>	// strcmp
#include <sys/mman.h>	// mmap

#include "hm_pair.h"


inline static const void *_hm_disktable_get(const char *mem, const char *key, uint64_t *ppos);
static int _hm_disktable_fwrite_junk(FILE *F, size_t count);


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
	return _hm_disktable_get(mmf->mem, key, NULL);
}

const void *hm_disktable_getp(const hm_disktable_t *mmf, const char *key, uint64_t *ppos){
	return _hm_disktable_get(mmf->mem, key, ppos);
}

const void *hm_disktable_getat(const hm_disktable_t *mmf, uint64_t pos){
	const char *mem = mmf->mem;

	const hm_disktable_fileformat_t *head = (hm_disktable_fileformat_t *) mem;
	uint64_t end = be64toh(head->size);

	if (pos >= end)
		return NULL;

	const uint64_t ptr = be64toh( head->data[pos] );
	const void *pair = & mem[ptr];

	return pair;
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

	const uint64_t start = ftello(F);
	const uint64_t datacount = hm_memtable_count(memtable);

	// write table header (currently size only)
	hm_disktable_fileformat_t header;
	header.size = htobe64(datacount);
	fwrite(& header, sizeof(header), 1, F);

	const uint64_t table_start = ftello(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	_hm_disktable_fwrite_junk(F, datacount);

	size_t i = 0;
	const void *it;
	const hm_pair_t *pair;
	for(pair = hm_memtable_it_first(memtable, &it); pair; pair = hm_memtable_it_next(memtable, &it)){
		// write item
		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_pair_fwrite(pair, F);

		// write pos
		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);

		++i;
	}

	return 0;
}

// =============================================

static const void *_hm_disktable_locate_bsearch(const char *mem, const char *key, uint64_t *ppos){
	if (key == NULL)
		return NULL;

	const hm_disktable_fileformat_t *head = (hm_disktable_fileformat_t *) mem;

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

inline static const void *_hm_disktable_get(const char *mem, const char *key, uint64_t *ppos){
	return _hm_disktable_locate_bsearch(mem, key, ppos);
}

static int _hm_disktable_fwrite_junk(FILE *F, size_t count){
	uint64_t be = 0xdeedbeef;

	size_t i;
	for(i = 0; i < count; i++)
		fwrite(& be, sizeof(uint64_t), 1, F);

	return 0;
}

