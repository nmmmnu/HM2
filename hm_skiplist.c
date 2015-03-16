#include "hm_skiplist_internal.h"

#include "hm_memtable.h"

#include <stdlib.h>	// NULL
#include <string.h>	// strcmp


hm_skiplist_t *hm_skiplist_create(hm_skiplist_t *l, hm_skiplist_height_t height){
	if (height == 0 || height > MAX_HEIGHT)
		height = DEF_HEIGHT;


	l->height = height;

	l->heads = malloc(2 * sizeof(void *) * (height + 1));

	if (l->heads == NULL)
		return NULL;

	l->loc = & l->heads[height];

	return _hm_skiplist_clear(l);
}

hm_skiplist_t *hm_skiplist_createa(hm_skiplist_height_t height){
	hm_skiplist_t *l = malloc(sizeof(hm_skiplist_t));

	if (l == NULL)
		return NULL;

	if (hm_skiplist_create(l, height))
		return l;

	free(l);

	return NULL;
}

void hm_skiplist_destroy(hm_skiplist_t *l){
	hm_skiplist_removeall(l);

	free(l->heads);
}

void hm_skiplist_removeall(hm_skiplist_t *l){
	hm_skiplist_node_t *copy;
	hm_skiplist_node_t *node;
	for(node = l->heads[0]; node; ){
		copy = node;

		node = node->next[0];

		hm_pair_free(copy->data);
		free(copy);
	}

	_hm_skiplist_clear(l);
}

int hm_skiplist_put(hm_skiplist_t *l, hm_pair_t *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_pair_getkey(newdata);

	hm_skiplist_node_t *node = (hm_skiplist_node_t *) _hm_skiplist_locate(l, key, 0);

	if (node){
		// update in place. node MUST be not NULL...

		hm_pair_t *olddata = node->data;

		// check if the data in database is valid
		if (! hm_pair_valid(newdata, olddata)){
			// prevent memory leak
			hm_pair_free(newdata);
			return 0;
		}

		// leave node, update only the data
		node->data = newdata;

		l->datasize = l->datasize
			- hm_pair_sizeof(olddata)
			+ hm_pair_sizeof(newdata);

		// release old data
		hm_pair_free(olddata);

		return 1;
	}

	// create new node

	unsigned char height = _hm_skiplist_height(l);

	hm_skiplist_node_t *newnode = malloc(sizeof(hm_skiplist_node_t) + height * sizeof(void *) );
	if (newnode == NULL){
		// prevent memory leak
		hm_pair_free(newdata);
		return 0;
	}

	newnode->height = height;
	newnode->data = newdata;

	// place new node where it belongs

	hm_skiplist_height_t i;
	for(i = 0; i < height; ++i){
		if (l->loc[i]){
			// we are at the middle
			hm_skiplist_node_t *node = l->loc[i];

			newnode->next[i] = node->next[i];
			node->next[i] = newnode;
		}else{
			newnode->next[i] = l->heads[i];
			l->heads[i] = newnode;
		}
	}

	l->datasize += hm_pair_sizeof(newdata);
	l->datacount++;

	return 1;
}

const hm_pair_t *hm_skiplist_get(const hm_skiplist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_skiplist_node_t *node = _hm_skiplist_locate(l, key, 0);

	if (node)
		return node->data;

	return NULL;
}

int hm_skiplist_remove(hm_skiplist_t *l, const char *key){
	if (key == NULL)
		return 0;

	hm_skiplist_node_t *node = (hm_skiplist_node_t *) _hm_skiplist_locate(l, key, 1);

	if ( ! node){
		// the key does not exists in the list.
		return 1;
	}

	hm_skiplist_height_t i;
	for(i = 0; i < l->height; ++i){
		hm_skiplist_node_t *prev = l->loc[i];

		if (prev){
			// check if lane go to this node...
			if (prev->next[i] == node)
				prev->next[i] = node->next[i];
		}else{
			// must be first
			if (l->heads[i] == node)
				l->heads[i] = node->next[i];
		}
	}

	l->datasize -= hm_pair_sizeof(node->data);
	l->datacount--;

	hm_pair_free(node->data);
	free(node);

	return 1;
}

size_t hm_skiplist_sizeof(const hm_skiplist_t *l){
	return l->datasize;
}

size_t hm_skiplist_count(const hm_skiplist_t *l){
	return l->datacount;
}

#if 0
size_t hm_skiplist_count(const hm_skiplist_t *l){
	size_t count = 0;

	const hm_skiplist_node_t *node;
	for(node = l->heads[0]; node; node = node->next[0]){
		++count;
	}

	return count;
}
#endif

void hm_skiplist_printf_lanes(const hm_skiplist_t *l){
	hm_skiplist_height_t i;
	for(i = l->height; i >= 0; --i){
		printf("Lane # %5u :\n", i - 1);
		_hm_skiplist_printf_lane(l, i - 1);
	}
}

const hm_pair_t *hm_skiplist_it_first(const hm_skiplist_t *l, const void **it){
	const hm_skiplist_node_t *node = l->heads[0];
	*it = node;

	return node ? node->data : NULL;
}

const hm_pair_t *hm_skiplist_it_next(const hm_skiplist_t *l,  const void **it){
	if (*it == NULL)
		return NULL;

	const hm_skiplist_node_t *node = *it;
	node = node->next[0];
	*it = node;

	return node ? node->data : NULL;
}

// ===============================================================

static hm_skiplist_t *_hm_skiplist_clear(hm_skiplist_t *l){
	l->datasize = 0;
	l->datacount = 0;

	memset(l->heads, 0, l->height * sizeof(void *) );

	// no need to clean l->loc

	return l;
}

static const hm_skiplist_node_t *_hm_skiplist_locate(const hm_skiplist_t *l, const char *key, int complete_evaluation){
	// it is extremly dangerous to have key == NULL here.
	if (key == NULL){
		_hm_error("FATAL ERROR", __FILE__, __LINE__);
	}

	// smart over-optimizations, such skip NULL lanes or
	// start from the middle of the list did not pay off.

	int cmp = 1;

	const hm_skiplist_node_t *node = NULL;
	const hm_skiplist_node_t *prev = NULL;

	hm_skiplist_height_t height = l->height;
	while(height){
		node = prev ? prev : l->heads[height - 1];

		while(node){
			cmp = strcmp(hm_pair_getkey(node->data), key);

			if (cmp >= 0)
				break;

			prev = node;
			node = node->next[height - 1];
		}


		if (cmp == 0 && complete_evaluation == 0)
			return node;

		l->loc[height - 1] = (void *) prev;

		--height;
	}

	return cmp ? NULL : node;
}

static unsigned char _hm_skiplist_height(const hm_skiplist_t *l){
	// This gives slightly better performance,
	// than divide by 3 or multply by 0.33
	int part = RAND_MAX >> 1;

	// We execute rand() inside the loop,
	// but performance is fast enought.

	hm_skiplist_height_t h = 1;
	while(h < l->height && rand() > part)
		++h;

	return h;

}

// ===============================================================

static void _hm_skiplist_printf_lane(const hm_skiplist_t *l, hm_skiplist_height_t lane){
	unsigned char i = 0;
	const hm_skiplist_node_t *node;
	for(node = l->heads[lane]; node; node = node->next[lane]){
		hm_pair_printf(node->data);

		if (i > 16)
			break;

		++i;
	}
}

// ===============================================================

hm_memtable_t *hm_memtable_createa(){
	return hm_skiplist_createa(0);
}

hm_memtable_t *hm_memtable_create(hm_memtable_t *a){
	return hm_skiplist_create(a, 0);
}

void hm_memtable_destroy(hm_memtable_t *a){
	hm_skiplist_destroy(a);
}

void hm_memtable_removeall(hm_memtable_t *a){
	hm_skiplist_removeall(a);
}

int hm_memtable_put(hm_memtable_t *a, hm_pair_t *pair){
	return hm_skiplist_put(a, pair);
}

const hm_pair_t *hm_memtable_get(const hm_memtable_t *a, const char *key){
	return hm_skiplist_get(a, key);
}

int hm_memtable_remove(hm_memtable_t *a, const char *key){
	return hm_skiplist_remove(a, key);
}

size_t hm_memtable_count(const hm_memtable_t *a){
	return hm_skiplist_count(a);
}

size_t hm_memtable_sizeof(const hm_memtable_t *a){
	return hm_skiplist_sizeof(a);
}

const hm_pair_t *hm_memtable_it_first(const hm_memtable_t *a, const void **it){
	return hm_skiplist_it_first(a, it);
}

const hm_pair_t *hm_memtable_it_next(const hm_memtable_t *a,  const void **it){
	return hm_skiplist_it_next(a, it);
}
