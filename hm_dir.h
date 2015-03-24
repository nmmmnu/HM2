#ifndef _HM_DIRECTORY_H
#define _HM_DIRECTORY_H


typedef struct _hm_dir_t hm_dir_t;
typedef struct _hm_dir_it_t hm_dir_it_t;


hm_dir_t *hm_dir_open(hm_dir_t *dir, const char *path);
hm_dir_t *hm_dir_opena(const char *path);

void hm_dir_close(hm_dir_t *dir);

hm_dir_t *hm_dir_reopen(hm_dir_t *dir);

const void *hm_dir_get(const hm_dir_t *dir, const char *key);

void hm_dir_printf(const hm_dir_t *dir);

#endif
