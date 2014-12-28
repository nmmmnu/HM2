#include "hm_linklist.h"

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>	// PRIu64



#define DUMP_FORMAT "%5" PRIu64 " : %-10s : %-20s : %12p : %12p\n"



static hm_linklist_t *_hm_linklist_clear(hm_linklist_t *l);



hm_linklist_t *hm_linklist_create(hm_linklist_t *l){
	return _hm_linklist_clear(l);
}

void hm_linklist_removeall(hm_linklist_t *l){
	hm_pair_t *copy;
	hm_pair_t *pair;
	for(pair = l->head; pair; ){
		copy = pair;

		pair = pair->next;

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

	hm_pair_t *prev = NULL;
	hm_pair_t *pair;
	for(pair = l->head; pair; pair = pair->next){
		int cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0){
			// handle delete

#ifdef HM_PAIR_EXPIRATION
			// check if the data in database is newer than "newpair"
			if (pair->created > newpair->created){
				// prevent memory leak
				free(newpair);
				return 0;
			}
#endif

			if (prev){
				// insert after prev
				prev->next = newpair;
			}else{
				// insert first
				l->head = newpair;
			}

			newpair->next = pair->next;
			free(pair);
			return 1;
		}

		if (cmp > 0)
			break;

		prev = pair;
	}

	// put new pair here...
	if (prev){
		// we are at the middle
		newpair-> next = prev->next;
		prev->next = newpair;
	}else{
		newpair->next = l->head;
		l->head = newpair;
	}

	return 1;
}

const hm_pair_t *hm_linklist_get(hm_linklist_t *l, const char *key){
	if (key == NULL)
		return NULL;

	const hm_pair_t *pair;
	for(pair = l->head; pair; pair = pair->next){
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

	hm_pair_t *prev = NULL;
	hm_pair_t *pair;
	for(pair = l->head; pair; pair = pair->next){
		int cmp = hm_pair_cmpkey(pair, key);

		if (cmp == 0){
			if (prev){
				prev->next = pair->next;
			}else{
				// First node...
				l->head = pair->next;
			}

			free(pair);
			return 1;
		}

		if (cmp > 0)
			break;

		prev = pair;
	}

	return 1;
}

hm_linklistsize_t hm_linklist_count(const hm_linklist_t *l){
	hm_linklistsize_t count = 0;

	const hm_pair_t *pair;
	for(pair = l->head; pair; pair = pair->next){
	//	if (hm_pair_valid(pair))
			count++;
	}

	return count;
}


void hm_linklist_dump(const hm_linklist_t *l){
	printf("LinkList  @ %p\n", l);

	//printf("LinkList->size = %" PRIu64 "\n", v->size);

	uint64_t i = 0;
	const hm_pair_t *pair;
	for(pair = l->head; pair; pair = pair->next){
		printf(DUMP_FORMAT,
			i,
			hm_pair_getkey(pair),
			hm_pair_getval(pair),
			pair,
			pair->next
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
















