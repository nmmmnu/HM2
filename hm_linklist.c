#include "hm_linklist.h"

#include <stdlib.h>
#include <string.h>	// strcmp



typedef struct _hm_linklist_node_t{
	void *next;		// system dependent
	void *data;		// system dependent
}hm_linklist_node_t;



static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l);


hm_linklist_t *hm_linklist_create(hm_linklist_t *l, hm_data_getkey_func_t getkey, hm_data_valid_func_t valid){
	l->getkey = getkey;
	l->valid = valid;

	return _hm_linklist_clear(l);
}

hm_list_t *hm_linklist_getlist(hm_linklist_t *ll){
	hm_list_t *l = malloc(sizeof(hm_list_t));

	if (l == NULL)
		return l;

	l->list		= ll;

	l->destroy	= (void (*)(void *))				hm_linklist_destroy;
	l->removeall	= (void (*)(void *))				hm_linklist_removeall;
	l->map		= (void (*)(const void *, hm_data_map_func_t))	hm_linklist_map;

	l->put		= (int (*)(void *, void *))			hm_linklist_put;
	l->get		= (const void *(*)(const void *, const char *))	hm_linklist_get;
	l->remove	= (int (*)(void *, const char *))		hm_linklist_remove;
	l->count	= (hm_listsize_t (*)(const void *))		hm_linklist_count;

	return l;
}

void hm_linklist_destroy(hm_linklist_t *l){
	hm_linklist_removeall(l);
}

void hm_linklist_removeall(hm_linklist_t *l){
	hm_linklist_node_t *copy;
	hm_linklist_node_t *node;
	for(node = l->head; node; ){
		copy = node;

		node = node->next;

		free(copy->data);
		free(copy);
	}

	_hm_linklist_clear(l);
}

int hm_linklist_put(hm_linklist_t *l, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = l->getkey(newdata);

	hm_linklist_node_t *newnode = malloc(sizeof(hm_linklist_node_t));
	if (newnode == NULL){
		// prevent memory leak
		free(newdata);
		return 0;
	}

	newnode->data = newdata;

	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *olddata = node->data;

		const int cmp = strcmp(l->getkey(olddata), key);

		if (cmp == 0){
			// handle delete

			if (l->valid){
				// check if the data in database is valid
				if (l->valid(newdata, olddata)){
					// prevent memory leak
					free(newdata);
					return 0;
				}
			}

			if (prev){
				// insert after prev
				prev->next = newnode;
			}else{
				// insert first
				l->head = newnode;
			}

			newnode->next = node->next;

			free(node->data);
			free(node);
			return 1;
		}

		if (cmp > 0)
			break;

		prev = node;
	}

	// put new pair here...
	if (prev){
		// we are at the middle
		newnode-> next = prev->next;
		prev->next = newnode;
	}else{
		newnode->next = l->head;
		l->head = newnode;
	}

	return 1;
}

const void *hm_linklist_get(const hm_linklist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *data = node->data;

		const int cmp = strcmp(l->getkey(data), key);

		if (cmp == 0)
			return data;

		if (cmp > 0)
			break;
	}

	return NULL;
}

int hm_linklist_remove(hm_linklist_t *l, const char *key){
	if (key == NULL)
		return 0;


	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *data = node->data;
		const int cmp = strcmp(l->getkey(data), key);

		if (cmp == 0){
			if (prev){
				prev->next = node->next;
			}else{
				// First node...
				l->head = node->next;
			}

			free(node->data);
			free(node);
			return 1;
		}

		if (cmp > 0)
			break;

		prev = node;
	}

	return 1;
}

hm_listsize_t hm_linklist_count(const hm_linklist_t *l){
	hm_listsize_t count = 0;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		count++;
	}

	return count;
}


void hm_linklist_map(const hm_linklist_t *l, hm_data_map_func_t map_func){
	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next)
		map_func(node->data);
}

// ===============================================================

static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l){
	l->head = NULL;

	return l;
}
















