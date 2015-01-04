#include "hm_pair.h"

#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



#define TIMESTAMP_MICROTIME_MULTIPLE 1 * 1000 * 1000

#define MAX_KEYSIZE	0xffff
#define MAX_VALSIZE	0xffffffff


#ifdef HM_PAIR_EXPIRATION
static hm_timestamp_t _hm_pair_now();
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

	uint64_t keylen = strlen(key) + 1;
	uint64_t vallen = strlen(val) + 1;

	if (keylen >= MAX_KEYSIZE || vallen >= MAX_VALSIZE)
		return NULL;

	hm_pair_t *pair = malloc( sizeof(hm_pair_t) + keylen + vallen);

	if (pair == NULL)
		return NULL;

#ifdef HM_PAIR_EXPIRATION
	pair->created	= _hm_pair_now();
	pair->expires	= expires;
#endif

	pair->keylen	= keylen;
	pair->vallen	= vallen;

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

	return _hm_pair_cmp(& pair->buffer[0], key, pair->keylen, strlen(key) + 1);
}

int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2){
	if (pair1 == NULL || pair2 == NULL)
		return 0;

	return _hm_pair_cmp(& pair1->buffer[0], & pair2->buffer[0], pair1->keylen, pair2->keylen);
}

#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair){
	if (! pair->expires)
		return 1;

	return pair->created + pair->expires * TIMESTAMP_MICROTIME_MULTIPLE > _hm_pair_now();
}
#endif

void hm_pair_dump(const hm_pair_t *pair){
	printf("%s @ %p{\n", "hm_pair_t", pair);
	printf("\t%-10s : %s\n", "key",		hm_pair_getkey(pair));
	printf("\t%-10s : %s\n", "value",	hm_pair_getval(pair));
	printf("}\n");
}

// ===============================================================

#ifdef HM_PAIR_EXPIRATION
static hm_timestamp_t _hm_pair_now(){
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return tv.tv_sec * TIMESTAMP_MICROTIME_MULTIPLE + tv.tv_usec;
}
#endif
