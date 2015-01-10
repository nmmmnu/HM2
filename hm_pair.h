#ifndef _HM_PAIR_H
#define _HM_PAIR_H

#include <stdint.h>
#include <endian.h>

#define HM_PAIR_EXPIRATION

#include <stdlib.h>	// size_t
#include <stdio.h>	// FILE *
#include <string.h>	// strlen



#ifdef HM_PAIR_EXPIRATION
typedef uint64_t hm_timestamp_t;
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



// Create pair

hm_pair_t *hm_pair_createnx(const char*key, const char*val, hm_valsize_t vallen, uint32_t expires);

inline static hm_pair_t *hm_pair_createn(const char*key, const char*val, hm_valsize_t vallen){
	return hm_pair_createnx(key, val, vallen, 0);
}

inline static hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires){
	hm_valsize_t vallen = val == NULL ? 0 : strlen(val);
	return hm_pair_createnx(key, val, vallen, expires);
}

inline static hm_pair_t *hm_pair_create(const char*key, const char*val){
	return hm_pair_createx(key, val, 0);
};

inline static hm_pair_t *hm_pair_createtombstone(const char*key){
	return hm_pair_create(key, NULL);
};



// sizeof

inline static size_t hm_pair_sizeof(const hm_pair_t *pair){
	return sizeof(hm_pair_t) + be16toh(pair->keylen) + 1 + be32toh(pair->vallen) + 1;
}



// Get key and value

inline static const char *hm_pair_getkey(const hm_pair_t *pair){
	return & pair->buffer[0];
}

inline static const char *hm_pair_getval(const hm_pair_t *pair){
	return & pair->buffer[ be16toh(pair->keylen) + 1 ];
}



// Cmp functions

inline static int hm_pair_cmpkey(const hm_pair_t *pair, const char *key){
	return key == NULL ? -1 : strcmp(hm_pair_getkey(pair), key);
}

inline static int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2){
	return strcmp(hm_pair_getkey(pair1), hm_pair_getkey(pair2));
}



// Misc functions

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
