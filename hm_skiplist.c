#include "hm_skiplist.h"

#include <stdlib.h>
#include <string.h>	// strcmp
#include <stdio.h>

#define MAX_HEIGHT 64
#define DEF_HEIGHT 32

typedef struct _hm_skiplist_node_t{
	void			*data;		// system dependent
	hm_skiplist_height_t	height;		// 1
	void			*next[];	// system dependent, dynamic, at least 1
}hm_skiplist_node_t;


static hm_skiplist_t *_hm_skiplist_clear(hm_skiplist_t *l);
static unsigned char _hm_skiplist_height(const hm_skiplist_t *l);
static const hm_skiplist_node_t *_hm_skiplist_locate(const hm_skiplist_t *l, const char *key, int complete_evaluation);

static void _hm_skiplist_printf_lane(const hm_skiplist_t *l, hm_skiplist_height_t lane);
static void _hm_skiplist_printf_more(const hm_skiplist_t *l);

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

		hm_listdata_free(copy->data);
		free(copy);
	}

	_hm_skiplist_clear(l);
}

int hm_skiplist_put(hm_skiplist_t *l, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_listdata_getkey(newdata);

	hm_skiplist_node_t *node = (hm_skiplist_node_t *) _hm_skiplist_locate(l, key, 0);

	if (node){
		// update in place. node MUST be not NULL...

		void *olddata = node->data;

		// check if the data in database is valid
		if (! hm_listdata_valid(newdata, olddata)){
			// prevent memory leak
			hm_listdata_free(newdata);
			return 0;
		}

		// leave node, update only the data
		node->data = newdata;

		l->datasize = l->datasize
			- hm_listdata_sizeof(olddata)
			+ hm_listdata_sizeof(newdata);

		// release old data
		hm_listdata_free(olddata);

		return 1;
	}

	// create new node

	unsigned char height = _hm_skiplist_height(l);

	hm_skiplist_node_t *newnode = malloc(sizeof(hm_skiplist_node_t) + height * sizeof(void *) );
	if (newnode == NULL){
		// prevent memory leak
		hm_listdata_free(newdata);
		return 0;
	}

	newnode->height = height;
	newnode->data = newdata;

	// place new node where it belongs

	hm_skiplist_height_t i;
	for(i = 0; i < height; i++){
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

	l->datasize += hm_listdata_sizeof(newdata);
	l->datacount++;

	return 1;
}

const void *hm_skiplist_get(const hm_skiplist_t *l, const char *key){
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
	for(i = 0; i < l->height; i++){
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

	l->datasize -= hm_listdata_sizeof(node->data);
	l->datacount--;

	hm_listdata_free(node->data);
	free(node);

	return 1;
}

#if 0
hm_listsize_t hm_skiplist_count(const hm_skiplist_t *l){
	hm_listsize_t count = 0;

	const hm_skiplist_node_t *node;
	for(node = l->heads[0]; node; node = node->next[0]){
		count++;
	}

	return count;
}
#endif

void hm_skiplist_printf_lanes(const hm_skiplist_t *l){
	hm_skiplist_height_t i;
	for(i = l->height; i > 0; i--){
		printf("Lane # %5u :\n", i - 1);
		_hm_skiplist_printf_lane(l, i - 1);
	}
}

int hm_skiplist_printf(const hm_skiplist_t *l, int more){
	if (more)
		_hm_skiplist_printf_more(l);

	_hm_skiplist_printf_lane(l, 0);

	return 0;
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
	// if key is NULL, is extremly dangerous to return NULL or anything else.

	int cmp = 1;

	const hm_skiplist_node_t *node = NULL;
	const hm_skiplist_node_t *prev = NULL;

	hm_skiplist_height_t height = l->height;
	while(height){
		node = prev ? prev : l->heads[height - 1];

		while(node){
			cmp = strcmp(hm_listdata_getkey(node->data), key);

			if (cmp >= 0)
				break;

			prev = node;
			node = node->next[height - 1];
		}


		if (cmp == 0 && complete_evaluation == 0)
			return node;

		l->loc[height - 1] = (void *) prev;

		height--;
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
		h++;

	return h;

}

// ===============================================================

static void _hm_print_heads(const hm_skiplist_t *l){
	hm_skiplist_height_t i;
	for(i = l->height; i > 0; i--)
		printf("\t\t%3u : %12p : %12p\n", i - 1, l->heads[i - 1], l->loc[i - 1]);
}

static void _hm_skiplist_printf_more(const hm_skiplist_t *l){
	printf("%s @ %p {\n", "hm_skiplist_t", l);

	printf("\theads{\n");
	_hm_print_heads(l);
	printf("\t}\n");

	printf("\t%-10s : %zu\n", "datasize", hm_skiplist_sizeof(l) );

	const hm_skiplist_node_t *node;
	for(node = l->heads[0]; node; node = node->next[0]){
		printf("\t%s @ %p {\n", "hm_skiplist_node_t", node);

		printf("\t\tnext {\n");
		hm_skiplist_height_t i;
		for(i = 0; i < node->height; i++)
			printf("\t\t\t[%3u] : %p\n", i, node->next[i]);
		printf("\t\t}\n");

		printf("\t\t%-10s : %u\n", "height",	node->height);
		printf("\t\t%-10s : %p\n", "data",	node->data);
		printf("\t}\n");
	}

	printf("}\n");
}

static void _hm_skiplist_printf_lane(const hm_skiplist_t *l, hm_skiplist_height_t lane){
	unsigned char i = 0;
	const hm_skiplist_node_t *node;
	for(node = l->heads[lane]; node; node = node->next[lane]){
		hm_listdata_printf(node->data);

		if (i > 16)
			break;

		i++;
	}
}
