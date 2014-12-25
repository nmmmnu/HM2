#ifndef _HM_PAIR_H
#define _HM_PAIR_H

#include <stdint.h>



typedef uint64_t timestamp_t;
typedef uint32_t expires_t;
typedef uint16_t keysize_t;
typedef uint32_t valsize_t;

typedef struct _hm_pair_t{
	void *		next;		// system dependent

	timestamp_t	created;	// 8
	expires_t	expires;	// 4, 136 years, not that bad.

	keysize_t	keylen;		// 2
	valsize_t	vallen;		// 4

	char		buffer[];	// dynamic
}hm_pair_t;



hm_pair_t *hm_pair_create(const char *key, const char *val);
hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires);

const char *hm_pair_getkey(const hm_pair_t *pair);
const char *hm_pair_getval(const hm_pair_t *pair);

int hm_pair_cmpkey(const hm_pair_t *pair, const char *key);
int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2);

int hm_pair_valid(const hm_pair_t *pair);

#endif
