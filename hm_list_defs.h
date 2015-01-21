#ifndef _HM_LIST_DEFS_H
#define _HM_LIST_DEFS_H

#include <stdlib.h>	// size_t
#include <stdio.h>	// FILE

typedef size_t hm_listsize_t;

void hm_list_free(void *item);

const char *hm_list_getkey(const void *item);
int hm_list_valid( const void *item1, const void *item2);
int hm_list_printf(const void *item);
int hm_list_fwrite(const void *item, FILE *F);

#endif
