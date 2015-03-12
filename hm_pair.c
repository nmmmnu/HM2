#include "hm_pair.h"

#include <string.h>	// memcpy, memcmp
#include <stdio.h>	// printf
#include <endian.h>	// htobe16


#define xmalloc(s) malloc(s)
#define xfree(p)   free(p)


#define MAX_KEYSIZE	( (hm_keysize_t) -1 )
#define MAX_VALSIZE	( (hm_valsize_t) -1 )


#ifdef HM_PAIR_CHECKSUM
typedef uint8_t hm_checksum_t;
#endif
#ifdef HM_PAIR_EXPIRATION
typedef uint64_t hm_timestamp_t;
typedef uint32_t hm_expires_t;		// 136 years, not that bad.
#endif


typedef struct _hm_pair_t{
#ifdef HM_PAIR_EXPIRATION
	hm_timestamp_t	created;	// 8
	hm_expires_t	expires;	// 4
#endif
	hm_valsize_t	vallen;		// 4
	hm_keysize_t	keylen;		// 2
#ifdef HM_PAIR_CHECKSUM
	hm_checksum_t	checksum;	// 1
#endif
	char		buffer[];	// dynamic
} __attribute__((__packed__)) hm_pair_t;
// yes, we *want* __attribute__ to give error on no-GCC


#ifdef HM_PAIR_EXPIRATION
#include <sys/time.h>
static hm_timestamp_t _hm_pair_now();
inline static hm_timestamp_t _hm_calc_time(uint32_t sec, uint32_t usec);
#endif


hm_pair_t *hm_pair_createnx(const char*key, const char*val, hm_valsize_t vallen, uint32_t expires){
	/*
	Assumptions:
	1. key   is string, up to uint16_t
	2. value is blob up to uint32_t
	3. after the key we store \0 byte, so we can use it as C string.
	4. after the value we store \0 byte, so we can use it as C string.
	*/

	if (key == NULL)
		return NULL;

	// because we need to to thombstones someday, we allow empty values
	// we do not need to change the val
	if (val == NULL)
		vallen = 0;

	hm_keysize_t keylen = strlen(key);

	if (keylen >= MAX_KEYSIZE || vallen >= MAX_VALSIZE)
		return NULL;

	hm_pair_t *pair = xmalloc(sizeof(hm_pair_t) + keylen + 1 + vallen + 1);

	if (pair == NULL)
		return NULL;

#ifdef HM_PAIR_EXPIRATION
	pair->created	= htobe64(_hm_pair_now());
	pair->expires	= htobe32(expires);
#endif

	pair->keylen	= htobe16(keylen);
	pair->vallen	= htobe32(vallen);

	// memcpy so we can switch to blobs later...
	memcpy(& pair->buffer[0], key, keylen);
	pair->buffer[keylen] = '\0';

	// this is safe with NULL pointer.
	memcpy(& pair->buffer[keylen + 1], val, vallen);
	pair->buffer[keylen + 1 + vallen] = '\0';

	// this is dummy method if no checksum
	hm_pair_checksummake(pair);

#if 0
	printf("hm_pair_t @ %12p\nbuffer %12p\nkey %u\nval %u\n", pair, pair->buffer, keylen, vallen);
	size_t i;
	for(i = 0; i < keylen + 1 + vallen + 1; i++)
		printf("%3zu | %3u | %2X | %c\n", i, pair->buffer[i], pair->buffer[i], pair->buffer[i]);
#endif

	return pair;
}

void hm_pair_free(hm_pair_t *pair){
	xfree(pair);
}

// sizeof

size_t hm_pair_sizeofbuffer(const hm_pair_t *pair){
	return be16toh(pair->keylen) + 1 + be32toh(pair->vallen) + 1;
}

size_t hm_pair_sizeof(const hm_pair_t *pair){
	return sizeof(hm_pair_t) + hm_pair_sizeofbuffer(pair);
}

// Get key and value

const char *hm_pair_getkey(const hm_pair_t *pair){
	return & pair->buffer[0];
}

const char *hm_pair_getval(const hm_pair_t *pair){
	return pair->vallen ? & pair->buffer[ be16toh(pair->keylen) + 1 ] : NULL;
}

// Cmp functions

int hm_pair_cmpkey(const hm_pair_t *pair, const char *key){
	return key == NULL ? -1 : strcmp(hm_pair_getkey(pair), key);
}

int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2){
	return strcmp(hm_pair_getkey(pair1), hm_pair_getkey(pair2));
}

#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2){
	if (! pair1->expires)
		return 1;

	return be64toh(pair1->created) + _hm_calc_time(be32toh(pair1->expires), 0) > _hm_pair_now();
}
#else
int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2){
	return 1;
}
#endif

#ifdef HM_PAIR_CHECKSUM
static hm_checksum_t _hm_pair_checksum(const hm_pair_t *pair);

void hm_pair_checksummake(hm_pair_t *pair){
	pair->checksum = _hm_pair_checksum(pair);
}

int hm_pair_checksumvalid(const hm_pair_t *pair){
	return pair->checksum == _hm_pair_checksum(pair);
}
#else
void hm_pair_checksummake(hm_pair_t *pair){
	/* noop */
}

int hm_pair_checksumvalid(const hm_pair_t *pair){
	return 1;
}
#endif


int hm_pair_fwrite(const hm_pair_t *pair, FILE *F){
	// new version, struct is packed and is in big endian
	// write data, return 0 in case of success
	return fwrite(pair, hm_pair_sizeof(pair), 1, F);
}

int hm_pair_printf(const hm_pair_t *pair){
	printf("| %s | %-12p | %-20s | %-20s |\n",
			"hm_pair_t",
			pair,
			hm_pair_getkey(pair),
			hm_pair_getval(pair)
	);

	return 0;
}

// ===============================================================

#ifdef HM_PAIR_CHECKSUM

static hm_checksum_t _hm_pair_checksum_real(const char *data2, size_t len){
	// NMEA 0183 like checksum
	const hm_checksum_t *data = (const hm_checksum_t *) data2;
	hm_checksum_t sum = 0;

	size_t i;
	for(i = 0; i < len; i++)
		sum = sum ^ data[i];

	return sum;
}

static hm_checksum_t _hm_pair_checksum(const hm_pair_t *pair){
	const char *vptr = (const char *) pair->buffer;

	// skip first byte
	return _hm_pair_checksum_real(vptr, hm_pair_sizeofbuffer(pair));
}

#endif

#ifdef HM_PAIR_EXPIRATION

inline static hm_timestamp_t _hm_calc_time(uint32_t sec, uint32_t usec){
	return (hm_timestamp_t) sec << 32 | usec;
}

static hm_timestamp_t _hm_pair_now(){
	struct timeval tv;

	gettimeofday(&tv, NULL);

	//return tv.tv_sec;

	return _hm_calc_time(tv.tv_sec, tv.tv_usec);
}

#endif
