#ifndef _HM_PAIR_H
#define _HM_PAIR_H

#include <stdint.h>
#include <endian.h>
#include <stdlib.h>	// size_t
#include <string.h>	// strlen
#include <stdio.h>	// FILE

//#define HM_PAIR_EXPIRATION
#define HM_PAIR_CHECKSUM


#ifdef HM_PAIR_CHECKSUM
typedef uint8_t hm_checksum_t;
#endif
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
	hm_valsize_t	vallen;		// 4
	hm_keysize_t	keylen;		// 2
#ifdef HM_PAIR_CHECKSUM
	hm_checksum_t	checksum;	// 1
#endif

	char		buffer[];	// dynamic

} __attribute__((__packed__)) hm_pair_t;
// yes, we *want* __attribute__ to give error on no-GCC


// Create pair

hm_pair_t *hm_pair_createnx(const char*key, const char*val, hm_valsize_t vallen, uint32_t expires);

inline static hm_pair_t *hm_pair_createn(const char*key, const char*val, hm_valsize_t vallen);
inline static hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires);
inline static hm_pair_t *hm_pair_create(const char*key, const char*val);
inline static hm_pair_t *hm_pair_createtombstone(const char*key);

void hm_pair_free(hm_pair_t *pair);

// sizeof

inline static size_t hm_pair_sizeof(const hm_pair_t *pair);


// Get key and value

inline static const char *hm_pair_getkey(const hm_pair_t *pair);
inline static const char *hm_pair_getval(const hm_pair_t *pair);


// Cmp functions

inline static int hm_pair_cmpkey(const hm_pair_t *pair, const char *key);
inline static int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2);


// Misc functions

#ifdef HM_PAIR_EXPIRATION
int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2);
#else
inline static int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2);
#endif

#ifdef HM_PAIR_CHECKSUM
void hm_pair_checksummake(hm_pair_t *pair);
int hm_pair_checksumvalid(const hm_pair_t *pair);
#else
inline static void hm_pair_checksummake(const hm_pair_t *pair);
inline static int hm_pair_checksumvalid(const hm_pair_t *pair);
#endif

int hm_pair_fwrite(const hm_pair_t *pair, FILE *F);
int hm_pair_printf(const hm_pair_t *pair);

#include "hm_pair_inlines.h"

#endif
