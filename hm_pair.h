#ifndef _HM_PAIR_H
#define _HM_PAIR_H

#include <stdint.h>
#include <endian.h>

#define HM_PAIR_EXPIRATION

#include <stdlib.h>	// size_t
#include <stdio.h>	// FILE *



#ifdef HM_PAIR_EXPIRATION
typedef uint32_t hm_timestamp_t;	// to be changed to uint64_t
typedef uint32_t hm_expires_t;		// 136 years, not that bad.
#endif
typedef uint16_t hm_keysize_t;
typedef uint32_t hm_valsize_t;



typedef struct _hm_pair_t{
#ifdef HM_PAIR_EXPIRATION
	hm_timestamp_t	created;	// 8
	hm_expires_t	expires;	// 4
#endif

	hm_keysize_t	keylen;		// 2
	hm_valsize_t	vallen;		// 4

	char		buffer[];	// dynamic

} __attribute__((__packed__)) hm_pair_t;
// yes, we *want* __attribute__ to give error on no-GCC



hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires);

inline static hm_pair_t *hm_pair_create(const char*key, const char*val){
	return hm_pair_createx(key, val, 0);
};

inline static size_t hm_pair_sizeof(const hm_pair_t *pair){
	return sizeof(hm_pair_t) + be16toh(pair->keylen) + be32toh(pair->vallen);
}

inline static const char *hm_pair_getkey(const hm_pair_t *pair){
	return & pair->buffer[0];
}

inline static const char *hm_pair_getval(const hm_pair_t *pair){
	return & pair->buffer[ be16toh(pair->keylen) ];
}

int hm_pair_cmpkey(const hm_pair_t *pair, const char *key);
int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2);

#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair);
#else
inline static int hm_pair_valid(const hm_pair_t *pair){
	return 1;
}
#endif

int hm_pair_fwrite(const hm_pair_t *pair, FILE *F);

void hm_pair_dump(const hm_pair_t *pair);

#endif
