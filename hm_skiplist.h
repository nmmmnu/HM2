#ifndef _HM_SKIPLIST_H
#define _HM_SKIPLIST_H

#include "hm_pair.h"

typedef unsigned char hm_skiplist_height_t;
typedef struct _hm_skiplist_t hm_skiplist_t;

typedef struct _hm_skiplist_it_t{
	const void	*p;
} hm_skiplist_it_t;

hm_skiplist_t *hm_skiplist_create(hm_skiplist_t *l, hm_skiplist_height_t height);
hm_skiplist_t *hm_skiplist_createa(hm_skiplist_height_t height);
void hm_skiplist_destroy(hm_skiplist_t *l);

void hm_skiplist_removeall(hm_skiplist_t *l);

int hm_skiplist_put(hm_skiplist_t *l, hm_pair_t *data);
const hm_pair_t *hm_skiplist_get(const hm_skiplist_t *l, const char *key);
int hm_skiplist_remove(hm_skiplist_t *l, const char *key);

size_t hm_skiplist_count(const hm_skiplist_t *l);
size_t hm_skiplist_sizeof(const hm_skiplist_t *l);

void hm_skiplist_printf_lanes(const hm_skiplist_t *l);

const hm_pair_t *hm_skiplist_it_first(const hm_skiplist_t *l, hm_skiplist_it_t *it);
const hm_pair_t *hm_skiplist_it_next(const hm_skiplist_t *l,  hm_skiplist_it_t *it);

#endif

