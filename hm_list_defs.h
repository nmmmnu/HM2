#ifndef _hm_listdata_DEFS_H
#define _hm_listdata_DEFS_H

#include <stdlib.h>	// size_t
#include <stdio.h>	// FILE

typedef size_t hm_listsize_t;

void hm_listdata_free(void *item);

const char *hm_listdata_getkey(const void *item);
int hm_listdata_valid( const void *item1, const void *item2);
int hm_listdata_printf(const void *item);
size_t hm_listdata_sizeof(const void *item);
int hm_listdata_fwrite(const void *item, FILE *F);

#endif
