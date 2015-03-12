#ifndef _HM_PAIR_H
#define _HM_PAIR_H

#include <stdint.h>
#include <stdlib.h>	// size_t
#include <string.h>	// strlen
#include <stdio.h>	// FILE


//#define HM_PAIR_EXPIRATION
#define HM_PAIR_CHECKSUM


typedef uint16_t hm_keysize_t;
typedef uint32_t hm_valsize_t;
typedef struct _hm_pair_t hm_pair_t;


// create / free pair

hm_pair_t *hm_pair_createnx(const char*key, const char*val, hm_valsize_t vallen, uint32_t expires);
void hm_pair_free(hm_pair_t *pair);


// create pair inlines

inline static hm_pair_t *hm_pair_createn(const char*key, const char*val, hm_valsize_t vallen);
inline static hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires);
inline static hm_pair_t *hm_pair_create(const char*key, const char*val);
inline static hm_pair_t *hm_pair_createtombstone(const char*key);

// sizeof

size_t hm_pair_sizeof(const hm_pair_t *pair);


// get key and value

const char *hm_pair_getkey(const hm_pair_t *pair);
const char *hm_pair_getval(const hm_pair_t *pair);


// cmp functions

int hm_pair_cmpkey(const hm_pair_t *pair, const char *key);
int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2);


// misc functions

int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2);
void hm_pair_checksummake(hm_pair_t *pair);
int hm_pair_checksumvalid(const hm_pair_t *pair);

int hm_pair_fwrite(const hm_pair_t *pair, FILE *F);
int hm_pair_printf(const hm_pair_t *pair);


// inlines

inline static hm_pair_t *hm_pair_createn(const char*key, const char*val, hm_valsize_t vallen){
	return hm_pair_createnx(key, val, vallen, 0);
}

inline static hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires){
	hm_valsize_t vallen = val == NULL ? 0 : strlen(val);
	return hm_pair_createnx(key, val, vallen, expires);
}

inline static hm_pair_t *hm_pair_create(const char*key, const char*val){
	return hm_pair_createx(key, val, 0);
}

inline static hm_pair_t *hm_pair_createtombstone(const char*key){
	return hm_pair_create(key, NULL);
}

#endif
