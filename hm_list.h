#ifndef _HM_LIST_H
#define _HM_LIST_H


#include <stdint.h>


typedef uint64_t hm_listsize_t;


typedef const char*(*hm_data_getkey_func_t)(const void *);
typedef const char*(*hm_data_valid_func_t)(const void *, const void *);

typedef void (*hm_data_map_func_t)(const void *);


// ================================

// simulate class virtual table

typedef struct _hm_list_t{
	void *list;

	void (*destroy)(void *list);
	void (*removeall)(void *list);

	void (*map)(const void *list, hm_data_map_func_t func);
	void (*dump)(const void *list);

	int (*put)(void *list, void *data);
	const void *(*get)(const void *list, const char *key);
	int (*remove)(void *list, const char *key);
	hm_listsize_t (*count)(const void *list);
} hm_list_t;


// ================================

// inject OO-style functions

static inline void hm_list_destroy(hm_list_t *list){
	list->destroy(list->list);
}

static inline void hm_list_removeall(hm_list_t *list){
	list->removeall(list->list);
}

static inline void hm_list_map(const hm_list_t *list, hm_data_map_func_t func){
	list->map(list->list, func);
}

static inline void hm_list_dump(const hm_list_t *list){
	list->dump(list->list);
}

static inline int hm_list_put(hm_list_t *list, void *data){
	return list->put(list->list, data);
}

static inline const void *hm_list_get(const hm_list_t *list, const char *key){
	return list->get(list->list, key);
}
static inline int hm_list_remove(hm_list_t *list, const char *key){
	return list->remove(list->list, key);
}

static inline hm_listsize_t hm_list_count(const hm_list_t *list){
	return list->count(list->list);
}

#endif
