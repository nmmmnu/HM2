#include "hm_linklist.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>	// PRIu64



#define DUMP_FORMAT "%5" PRIu64 " : %-10s : %-20s : %12p : %12p\n"



typedef struct _hm_linklist_node_t{
	void *next;		// system dependent
	void *data;		// system dependent
}hm_linklist_node_t;



static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l);



hm_linklist_t *hm_linklist_create(hm_linklist_t *l){
	return _hm_linklist_clear(l);
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

void hm_linklist_destroy(hm_linklist_t *l){
	hm_linklist_removeall(l);
}

int hm_linklist_put(hm_linklist_t *l, hm_pair_t *newpair){
	if (newpair == NULL)
		return 0;

	const char *key = hm_pair_getkey(newpair);

	hm_linklist_node_t *newnode = malloc(sizeof(hm_linklist_node_t));
	if (newnode == NULL){
		// prevent memory leak
		free(newpair);
		return 0;
	}

	newnode->data = newpair;

	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		hm_pair_t *pair = node->data;

		int cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0){
			// handle delete

#ifdef HM_PAIR_EXPIRATION
			// check if the data in database is newer than "newpair"
			if (pair->created > newpair->created){
				// nothing to insert
				// prevent memory leak
				free(newpair);
				return 0;
			}
#endif
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

const hm_pair_t *hm_linklist_get(hm_linklist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const hm_pair_t *pair = node->data;

		int cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0)
			return hm_pair_valid(pair) ? pair : NULL;

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
		int cmp = hm_pair_cmpkey(node->data, key);

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

hm_linklistsize_t hm_linklist_count(const hm_linklist_t *l){
	hm_linklistsize_t count = 0;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
	//	if (hm_pair_valid(pair))
			count++;
	}

	return count;
}


void hm_linklist_dump(const hm_linklist_t *l){
	printf("LinkList  @ %p\n", l);

	//printf("LinkList->size = %" PRIu64 "\n", v->size);

	uint64_t i = 0;
	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const hm_pair_t *pair = node->data;

		printf(DUMP_FORMAT,
			i,
			hm_pair_getkey(pair),
			hm_pair_getval(pair),
			node,
			node->next
		);

		i++;
	}

	if (i == 0){
		printf("No pairs found...\n");
	}

	printf("\n");
}

// ===============================================================

static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l){
	l->head = NULL;

	return l;
}
















