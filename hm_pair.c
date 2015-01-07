#include "hm_pair.h"

#include <string.h>	// memcpy, memcmp
#include <endian.h>	// htobe16


#define MAX_KEYSIZE	0xffff
#define MAX_VALSIZE	0xffffffff


#ifdef HM_PAIR_EXPIRATION
#include <sys/time.h>

static hm_timestamp_t _hm_pair_now();
inline static hm_timestamp_t _hm_calc_time(uint32_t sec, uint32_t usec);
#endif


hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires){
	/*
	For the moment, we assume key and value are strings.

	In first version, we kept the character data inside the buffer,
	and skipped the last \0 terminating character.

	By this way we "save" 2 bytes.

	However examinig memory allocation shows, that memory used is
	much more than memory allocated.

	By this reason we will put the terminating character,
	so we can pass key and value back to the client using refference
	to stored value. Comparrisson will work easyer and better too.
	*/

	if (key == NULL || val == NULL)
		return NULL;

	hm_keysize_t keylen = strlen(key) + 1;
	hm_valsize_t vallen = strlen(val) + 1;

	if (keylen >= MAX_KEYSIZE || vallen >= MAX_VALSIZE)
		return NULL;

	hm_pair_t *pair = malloc(sizeof(hm_pair_t) + keylen + vallen);

	if (pair == NULL)
		return NULL;

#ifdef HM_PAIR_EXPIRATION
	pair->created	= htobe64(_hm_pair_now());
	pair->expires	= htobe32(expires);
#endif

	pair->keylen	= htobe16(keylen);
	pair->vallen	= htobe32(vallen);

	// memcpy so we can switch to blobs later...
	memcpy(& pair->buffer[0     ], key, keylen);
	memcpy(& pair->buffer[keylen], val, vallen);

	return pair;
}

static int _hm_pair_cmp(const void *m1, const void *m2, hm_keysize_t size1, hm_keysize_t size2){
	if (size1 == size2)
		return memcmp(m1, m2, size1);

	if (size1 < size2){
		int x =  memcmp(m1, m2, size1);
		return x ? x : -1;
	}else{
		int x =  memcmp(m1, m2, size2);
		return x ? x : +1;
	}
}

int hm_pair_cmpkey(const hm_pair_t *pair, const char *key){
	if (key == NULL)
		return -1;

	return _hm_pair_cmp(& pair->buffer[0], key, be16toh(pair->keylen), strlen(key) + 1);
}

int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2){
	if (pair1 == NULL || pair2 == NULL)
		return 0;

	return _hm_pair_cmp(& pair1->buffer[0], & pair2->buffer[0], be16toh(pair1->keylen), be16toh(pair2->keylen));
}

#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair){
	if (! pair->expires)
		return 1;

	return be64toh(pair->created) + _hm_calc_time(be32toh(pair->expires), 0) > _hm_pair_now();
}
#endif

int hm_pair_fwrite(const hm_pair_t *pair, FILE *F){
	// new version, struct is packed and is in big endian

	// this one is pretty short, but we want to be linked

	// write data, return 0 in case of success
	return ! fwrite(pair, hm_pair_sizeof(pair), 1, F);
}

void hm_pair_dump(const hm_pair_t *pair){
	printf("%s @ %p{\n", "hm_pair_t", pair);
	printf("\t%-10s : %s\n", "key",		hm_pair_getkey(pair));
	printf("\t%-10s : %s\n", "value",	hm_pair_getval(pair));
	printf("}\n");
}

// ===============================================================

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

// ===============================================================

/*

// old version with aligned struct and rasterize
int hm_pair_fwrite(const hm_pair_t *pair, FILE *F){
	char buffer[ sizeof(hm_pair_t) ];

	unsigned char pos = 0;
	uint16_t *be16;
	uint32_t *be32;

	// "rasterize" numbers

#ifdef HM_PAIR_EXPIRATION
	be32 = (uint32_t *) & buffer[pos];	pos = pos + sizeof(uint32_t);	*be32 = htobe32(pair->created);
	be32 = (uint32_t *) & buffer[pos];	pos = pos + sizeof(uint32_t);	*be32 = htobe32(pair->expires);
#endif
	be16 = (uint16_t *) & buffer[pos];	pos = pos + sizeof(uint16_t);	*be16 = htobe16(pair->keylen);
	be32 = (uint32_t *) & buffer[pos];	pos = pos + sizeof(uint32_t);	*be32 = htobe32(pair->vallen);

	// write numbers at once
	if (fwrite(buffer, pos, 1, F) == 0)
		return -1;

	// write data
	if (fwrite(pair->buffer, pair->keylen + pair->vallen, 1, F) == 0)
		return -1;

	// done
	return 0;
}
*/
