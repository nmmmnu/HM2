#ifndef _HM_MEMTABLE_H
#define _HM_MEMTABLE_H

#include "hm_pair.h"


typedef void hm_memtable_t;

typedef void hm_memtable_it_t;


hm_memtable_t *hm_memtable_createa();
hm_memtable_t *hm_memtable_create(hm_memtable_t *a);
void hm_memtable_destroy(hm_memtable_t *a);

void hm_memtable_removeall(hm_memtable_t *a);

int hm_memtable_put(hm_memtable_t *a, hm_pair_t *pair);
const hm_pair_t *hm_memtable_get(const hm_memtable_t *a, const char *key);
int hm_memtable_remove(hm_memtable_t *a, const char *key);

size_t hm_memtable_count(const hm_memtable_t *a);
size_t hm_memtable_sizeof(const hm_memtable_t *a);

hm_memtable_it_t *hm_memtable_it_open(const hm_memtable_t *l);
void hm_memtable_it_close(hm_memtable_it_t *it);

const hm_pair_t *hm_memtable_it_first(hm_memtable_it_t *it);
const hm_pair_t *hm_memtable_it_next(hm_memtable_it_t *it);

#endif
