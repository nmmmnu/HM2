#include "hm_pair.h"

#include <string.h>	// memcpy, memcmp
#include <stdio.h>	// printf
#include <endian.h>	// htobe16


#define MAX_KEYSIZE	0xffff
#define MAX_VALSIZE	0xffffffff


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

	hm_pair_t *pair = malloc(sizeof(hm_pair_t) + keylen + 1 + vallen + 1);

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
	pair->buffer[keylen] = '\0';

	// this is safe with NULL pointer.
	memcpy(& pair->buffer[keylen + 1], val, vallen);
	pair->buffer[keylen + 1 + vallen] = '\0';

//	unsigned int i;
//	for(i = 0; i < keylen + 1 + vallen + 1; i++)
//		printf("%5u : %5d : %c\n", i, pair->buffer[i], pair->buffer[i]);
//	exit(0);

	return pair;
}


#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2){
	if (! pair1->expires)
		return 1;

	return be64toh(pair1->created) + _hm_calc_time(be32toh(pair1->expires), 0) > _hm_pair_now();
}
#endif

int hm_pair_fwrite(const hm_pair_t *pair, FILE *F){
	// new version, struct is packed and is in big endian

	// this one is pretty short, but we want to be linked

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

	//return _hm_pair_cmp(& pair->buffer[0], key, be16toh(pair->keylen), strlen(key));
	//return _hm_pair_cmp(& pair1->buffer[0], & pair2->buffer[0], be16toh(pair1->keylen), be16toh(pair2->keylen));
*/
