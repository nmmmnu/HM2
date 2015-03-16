#ifndef _HM_SKIPLIST_INTERNAL_H
#define _HM_SKIPLIST_INTERNAL_H

#include "hm_skiplist.h"

#include <stdlib.h>	// exit


#define MAX_HEIGHT 64
#define DEF_HEIGHT 32


typedef struct _hm_skiplist_t{
	size_t			datasize;	// system dependent
	size_t			datacount;	// system dependent

	hm_skiplist_height_t	height;		// 1

	void			**heads;	// system dependent, dynamic, at least 1
	void			**loc;		// system dependent, dynamic, at least 1
} hm_skiplist_t;


typedef struct _hm_skiplist_node_t{
	hm_pair_t		*data;		// system dependent
	hm_skiplist_height_t	height;		// 1
	void			*next[];	// system dependent, dynamic, at least 1
} hm_skiplist_node_t;


static hm_skiplist_t *_hm_skiplist_clear(hm_skiplist_t *l);
static unsigned char _hm_skiplist_height(const hm_skiplist_t *l);
static const hm_skiplist_node_t *_hm_skiplist_locate(const hm_skiplist_t *l, const char *key, int complete_evaluation);

static void _hm_skiplist_printf_lane(const hm_skiplist_t *l, hm_skiplist_height_t lane);

inline static void _hm_error(const char *err, const char *file, unsigned int line){
	fprintf(stderr, "%s: key is NULL on %s:%u\n", err, file, line);
	exit(100);
}

#endif
