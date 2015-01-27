#include "hm_linklist.h"

#include <stdlib.h>
#include <string.h>	// strcmp
#include <stdio.h>



typedef struct _hm_linklist_node_t{
	void *next;		// system dependent
	void *data;		// system dependent
}hm_linklist_node_t;



static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l);


hm_linklist_t *hm_linklist_create(hm_linklist_t *l){
	return _hm_linklist_clear(l);
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

		hm_list_free(copy->data);
		free(copy);
	}

	_hm_linklist_clear(l);
}

int hm_linklist_put(hm_linklist_t *l, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_list_getkey(newdata);

	hm_linklist_node_t *newnode = malloc(sizeof(hm_linklist_node_t));
	if (newnode == NULL){
		// prevent memory leak
		hm_list_free(newdata);
		return 0;
	}

	newnode->data = newdata;
	l->datasize += hm_list_sizeof(newdata);

	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *olddata = node->data;

		const int cmp = strcmp(hm_list_getkey(olddata), key);

		if (cmp == 0){
			// handle delete

			// check if the data in database is valid
			if (! hm_list_valid(newdata, olddata)){
				// prevent memory leak
				hm_list_free(newdata);
				return 0;
			}

			if (prev){
				// insert after prev
				prev->next = newnode;
			}else{
				// insert first
				l->head = newnode;
			}

			newnode->next = node->next;

			l->datasize -= hm_list_sizeof(node->data);

			hm_list_free(node->data);
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
		newnode->next = prev->next;
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

		const int cmp = strcmp(hm_list_getkey(data), key);

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
		const int cmp = strcmp(hm_list_getkey(data), key);

		if (cmp == 0){
			if (prev){
				prev->next = node->next;
			}else{
				// First node...
				l->head = node->next;
			}

			l->datasize -= hm_list_sizeof(node->data);
			hm_list_free(node->data);
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

static void _hm_linklist_printf_more(const hm_linklist_t *l){
	printf("%s @ %p {\n", "hm_linklist_t", l);

	printf("\t%-10s : %zu\n", "datasize", hm_linklist_sizeof(l) );

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		printf("\t%s @ %p {\n", "hm_linklist_node_t", node);
		printf("\t\t%-10s : %p\n", "next", node->next);
		printf("\t\t%-10s : %p\n", "data", node->data);
		printf("\t}\n");
	}

	printf("}\n");
}

int hm_linklist_printf(const hm_linklist_t *l, int more){
	if (more)
		_hm_linklist_printf_more(l);

	unsigned char i = 0;
	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		hm_list_printf(node->data);

		if (i > 16){
			break;
		}

		i++;
	}

	return 0;
}

// ===============================================================

static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l){
	l->datasize = 0;
	l->head = NULL;

	return l;
}
















