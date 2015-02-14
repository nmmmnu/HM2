#ifndef _HM_SKIPLIST_H
#define _HM_SKIPLIST_H


#include "hm_list_defs.h"

typedef unsigned char	hm_skiplist_height_t;

typedef struct _hm_skiplist_t{
	size_t			datasize;	// system dependent
	size_t			datacount;	// system dependent
	hm_skiplist_height_t	height;		// 1
	void			**heads;	// system dependent, dynamic, at least 1
	void			**loc;		// system dependent, dynamic, at least 1
}hm_skiplist_t;


hm_skiplist_t *hm_skiplist_create(hm_skiplist_t *l, hm_skiplist_height_t height);

void hm_skiplist_destroy(hm_skiplist_t *l);

void hm_skiplist_removeall(hm_skiplist_t *l);

int hm_skiplist_put(hm_skiplist_t *l, void *data);

const void *hm_skiplist_get(const hm_skiplist_t *l, const char *key);

int hm_skiplist_remove(hm_skiplist_t *l, const char *key);

inline static hm_listsize_t hm_skiplist_count(const hm_skiplist_t *l){
	return l->datacount;
}

inline static size_t hm_skiplist_sizeof(const hm_skiplist_t *l){
	return l->datasize;
}

int hm_skiplist_printf(const hm_skiplist_t *l, int more);

void hm_skiplist_printf_lanes(const hm_skiplist_t *l);

#endif
