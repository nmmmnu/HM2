#ifndef _HM_DISKTABLE_H
#define _HM_DISKTABLE_H

#include "hm_memtable.h"

#include <stdio.h>	// off_t, FILE
#include <stdint.h>	// uint64_t

typedef struct _hm_disktable_t hm_disktable_t;

typedef struct _hm_disktable_it_t hm_disktable_it_t;

hm_disktable_t *hm_disktable_open(hm_disktable_t *mmf, const char *filename);
hm_disktable_t *hm_disktable_opena(const char *filename);
void hm_disktable_close(hm_disktable_t *mmf);
off_t hm_disktable_count(const hm_disktable_t *mmf);

const void *hm_disktable_get(const hm_disktable_t *mmf, const char *key);
const void *hm_disktable_getat(const hm_disktable_t *mmf, uint64_t pos);

hm_disktable_it_t *hm_disktable_it_open(const hm_disktable_t *mmf);
void hm_disktable_it_close(hm_disktable_it_t *it);

const hm_pair_t *hm_disktable_it_first(hm_disktable_it_t *it);
const hm_pair_t *hm_disktable_it_next(hm_disktable_it_t *it);

int hm_disktable_createfrommemtable(const hm_memtable_t *memtable, const char *filename_to_write);
int hm_disktable_createfrommemtablef(const hm_memtable_t *memtable, FILE *F);

#endif
