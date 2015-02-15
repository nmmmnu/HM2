#include "hm_linklist.h"

#include <stdlib.h>
#include <string.h>	// strcmp



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

		hm_listdata_free(copy->data);
		free(copy);
	}

	_hm_linklist_clear(l);
}

int hm_linklist_put(hm_linklist_t *l, void *newdata){
	if (newdata == NULL)
		return 0;

	const char *key = hm_listdata_getkey(newdata);

	hm_linklist_node_t *prev = NULL;
	hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *olddata = node->data;

		const int cmp = strcmp(hm_listdata_getkey(olddata), key);

		if (cmp == 0){
			// handle overwrite,
			// keep the node, overwrite the data

			// check if the data in database is valid
			if (! hm_listdata_valid(newdata, olddata)){
				// prevent memory leak
				hm_listdata_free(newdata);
				return 0;
			}

			l->datasize = l->datasize
				- hm_listdata_sizeof(node->data)
				+ hm_listdata_sizeof(newdata);

			hm_listdata_free(node->data);
			node->data = newdata;

			return 1;
		}

		if (cmp > 0)
			break;

		prev = node;
	}

	hm_linklist_node_t *newnode = malloc(sizeof(hm_linklist_node_t));
	if (newnode == NULL){
		// prevent memory leak
		hm_listdata_free(newdata);
		return 0;
	}

	newnode->data = newdata;

	// put new pair here...
	if (prev){
		// we are at the middle
		newnode->next = prev->next;
		prev->next = newnode;
	}else{
		newnode->next = l->head;
		l->head = newnode;
	}

	l->datasize += hm_listdata_sizeof(newdata);
	l->datacount++;

	return 1;
}

const void *hm_linklist_get(const hm_linklist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		const void *data = node->data;

		const int cmp = strcmp(hm_listdata_getkey(data), key);

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
		const int cmp = strcmp(hm_listdata_getkey(data), key);

		if (cmp == 0){
			if (prev){
				prev->next = node->next;
			}else{
				// First node...
				l->head = node->next;
			}

			l->datasize -= hm_listdata_sizeof(node->data);
			l->datacount--;

			hm_listdata_free(node->data);
			free(node);
			return 1;
		}

		if (cmp > 0)
			break;

		prev = node;
	}

	return 1;
}

#if 0
hm_listsize_t hm_linklist_count(const hm_linklist_t *l){
	hm_listsize_t count = 0;

	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		count++;
	}

	return count;
}
#endif

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
		hm_listdata_printf(node->data);

		if (i > 16){
			break;
		}

		i++;
	}

	return 0;
}

int hm_linklist_fwrite(const hm_linklist_t *l, FILE *F){
	uint64_t be;

	const uint64_t start = ftello(F);

	// write table header (currently size only)
	hm_fileformat_line_t header;
	header.size = htobe64( (uint64_t) l->datacount );
	fwrite(& header, sizeof(header), 1, F);

	const uint64_t table_start = ftello(F);

	// write junk zero table.
	// this is made in order to expand the file size.
	_hm_file_fwrite_junk(F, l->datacount);

	hm_listsize_t i = 0;
	const hm_linklist_node_t *node;
	for(node = l->head; node; node = node->next){
		// write item
		fseeko(F, 0, SEEK_END);
		const uint64_t abspos = ftello(F);

		hm_listdata_fwrite(node->data, F);

		// write pos
		fseeko(F, table_start + sizeof(uint64_t) * i, SEEK_SET);
		be = htobe64(abspos - start);
		fwrite(& be, sizeof(uint64_t), 1, F);

		i++;
	}

	// file written (hopefully)

	return 0;
}

// ===============================================================

static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l){
	l->datasize = 0;
	l->datacount = 0;
	l->head = NULL;

	return l;
}

