#include "hm_vector.h"

#include <stdlib.h>
#include <string.h>	// memmove, strcmp
#include <endian.h>	// htobe16
#include <stdint.h>
//#include <inttypes.h>	// PRIu64



#define DEFAULT_REALLOC_CHUNK_SIZE 1 * sizeof(void *)


static hm_vector_t *_hm_vector_clear(hm_vector_t *v, int also_free);
static int _hm_vector_locate_position(const hm_vector_t *v, const char *key, hm_listsize_t *index);
static int _hm_vector_shiftL(hm_vector_t *v, hm_listsize_t index);
static int _hm_vector_shiftR(hm_vector_t *v, hm_listsize_t index);


hm_vector_t *hm_vector_create(hm_vector_t *v, size_t realloc_chunk_size){
	v->realloc_chunk_size = realloc_chunk_size ? realloc_chunk_size : DEFAULT_REALLOC_CHUNK_SIZE;

	return _hm_vector_clear(v, 0);
}

void hm_vector_removeall(hm_vector_t *v){
	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		void *data = v->buffer[i];

		if (data)
			hm_listdata_free(data);
	}

	_hm_vector_clear(v, 1);
}

void hm_vector_destroy(hm_vector_t *v){
	hm_vector_removeall(v);
}

int hm_vector_put(hm_vector_t *v, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_listdata_getkey(newdata);

	hm_listsize_t index;
	int cmp = _hm_vector_locate_position(v, key, & index);

	if (cmp == 0){
		// key exists, overwrite, do not shift

		void *olddata = v->buffer[index];

		// check if the data in database is valid
		if (! hm_listdata_valid(newdata, olddata) ){
			// prevent memory leak
			hm_listdata_free(newdata);
			return 0;
		}

		v->datasize = v->datasize
					- hm_listdata_sizeof(olddata)
					+ hm_listdata_sizeof(newdata);

		hm_listdata_free(olddata);

		v->buffer[index] = newdata;
		return 1;
	}

	if ( ! _hm_vector_shiftR(v, index) ){
		// prevent memory leak
		hm_listdata_free(newdata);
		return 0;
	}

	v->datasize += hm_listdata_sizeof(newdata);
	v->buffer[index] = newdata;
	return 1;
}

const void *hm_vector_get(const hm_vector_t *v, const char *key){
	if (key == NULL)
		return NULL;

	hm_listsize_t index;
	if (_hm_vector_locate_position(v, key, & index) == 0)
		return v->buffer[index];

	return NULL;
}

int hm_vector_remove(hm_vector_t *v, const char *key){
	hm_listsize_t index;
	int cmp = _hm_vector_locate_position(v, key, & index);

	if (cmp){
		// the key does not exists in the vector.
		return 1;
	}

	// proceed with remove
	void *data = v->buffer[index];
	v->datasize -= hm_listdata_sizeof(data);
	hm_listdata_free(data);

	_hm_vector_shiftL(v, index);

	return 1;
}

static void _hm_vector_printf_more(const hm_vector_t *v){
	printf("%s @ %p {\n", "hm_vector_t", v);

	printf("\t%-10s : %10zu\n", "size",		(size_t)v->size);
	printf("\t%-10s : %10zu\n", "datasize",		hm_vector_sizeof(v) );
	printf("\t%-10s : %10zu\n", "realloc...",	v->realloc_chunk_size);
	printf("\t%-10s : %10zu\n", "buffer...",	v->buffer_alloc_size);
	printf("\t%-10s : %10zu\n", "waste mem",	v->buffer_alloc_size - v->size * sizeof(void *));

	printf("\t%-10s : [\n", "buffer");
	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		printf("\t\t%p\n", v->buffer[i]);

		if (i > 16){
			printf("\t\t...\n");
			break;
		}
	}
	printf("\t]\n");

	printf("}\n");
}

int hm_vector_printf(const hm_vector_t *v, int more){
	if (more)
		_hm_vector_printf_more(v);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		hm_listdata_printf(v->buffer[i]);

		if (i > 16){
			break;
		}
	}

	return 0;
}

int hm_vector_fwrite(const hm_vector_t *v, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);

	// write table header (currently size only)
	hm_fileformat_line_t header;
	header.size = htobe64( (uint64_t) v->size );
	fwrite(& header, sizeof(header), 1, F);

	const uint64_t table_start = ftello(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	_hm_file_fwrite_junk(F, v->size);

	hm_listsize_t i;
	for(i = 0; i < v->size; i++){
		// write item
		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_listdata_fwrite(v->buffer[i], F);

		// write pos
		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);
	}

	// file written (hopefully)

	return 0;
}

// ===============================================================

static hm_vector_t *_hm_vector_clear(hm_vector_t *v, int also_free){
	if (also_free && v->buffer)
		free(v->buffer);

	v->size = 0;
	v->datasize = 0;
	v->buffer_alloc_size = 0;
	v->buffer = NULL;

	return v;
}

static size_t _hm_vector_calcnewsize(size_t size, size_t realloc_chunk_size){
	size_t newsize = size / realloc_chunk_size;

	if (size % realloc_chunk_size)
		newsize++;

	return newsize * realloc_chunk_size;
}

static inline void *xrealloc(void *buffer, size_t size){
	//printf("realloc(): %12zu\n", size);

	return realloc(buffer, size);
}

static int _hm_vector_resize(hm_vector_t *v, int delta){
	if (delta == 0){
		// already resized, done :)
		return 1;
	}

	if (delta > 1)
		delta = 1;

	if (delta < -1)
		delta = -1;

	hm_listsize_t new_size = v->size + delta;

	if (new_size == 0){
		_hm_vector_clear(v, 1);
		return 1;
	}

	size_t new_buffer_alloc_size = _hm_vector_calcnewsize(new_size * sizeof(void *), v->realloc_chunk_size);

	if (v->buffer_alloc_size == new_buffer_alloc_size){
		// already resized, done :)
		v->size = new_size;

		return 1;
	}

	void *new_buffer = xrealloc(v->buffer, new_buffer_alloc_size);

	if (new_buffer == NULL)
		return 0;

	v->size			= new_size;
	v->buffer_alloc_size	= new_buffer_alloc_size;
	v->buffer		= new_buffer;

	return 1;
}

static int _hm_vector_locate_position_bsearch(const hm_vector_t *v, const char *key, hm_listsize_t *index){

	/*
	 * Lazy based from Linux kernel...
	 * http://lxr.free-electrons.com/source/lib/bsearch.c
	 */

	hm_listsize_t start = 0;
	hm_listsize_t end = v->size;
	int cmp = 0;

	while (start < end){
	//	hm_listsize_t mid = start + ((end - start) /  2);
		hm_listsize_t mid = start + ((end - start) >> 1);

		const void *data = v->buffer[mid];

		cmp = strcmp(hm_listdata_getkey(data), key);

		if (cmp == 0){
			*index = mid;
			return 0;
		}

		if (cmp < 0){
			// go right
			start = mid + 1;
		}else{
			// go left
			end = mid;
		}
	}

	*index = start;
	return cmp;
}

static int _hm_vector_locate_position(const hm_vector_t *v, const char *key, hm_listsize_t *index){
	if (v->size == 0){
		*index = 0;
		return 1;
	}

	return _hm_vector_locate_position_bsearch(v, key, index);
}

static int _hm_vector_shiftR(hm_vector_t *v, hm_listsize_t index){
	if (! _hm_vector_resize(v, 1))
		return 0;

	// this is the most slow operation of them all
	memmove(& v->buffer[index + 1], & v->buffer[index], (v->size - index - 1) * sizeof(void *));

	return 1;
}

static int _hm_vector_shiftL(hm_vector_t *v, hm_listsize_t index){
	// this is the most slow operation of them all
	memmove(& v->buffer[index], & v->buffer[index + 1], (v->size - index) * sizeof(void *));

	_hm_vector_resize(v, -1);

	return 1;
}


