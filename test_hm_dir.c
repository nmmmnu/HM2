#include "hm_pair.h"
#include "hm_dir.h"

#include <stdio.h>

#include <stdlib.h>	// NULL

static void print_usage(const char *name){
	printf("Usage:\n");
	printf("\t%s [directory] [key] - find in the database\n", name);
	printf("\t\tDo not forget about quotes around the directory\n");
}

static void dir_open_test(hm_dir_t *dir, const char *keytofind){
	if (dir == NULL){
		printf("Can not open database\n");
		exit(1);
	}

	hm_dir_printf(dir);

	const hm_pair_t *pair = hm_dir_get(dir, keytofind);

	if (pair){
		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}else{
		printf("Not Found\n");
	}
}

int main(int argc, char **argv){
	if (argc < 2){
		print_usage(argv[0]);
		return 1;
	}

	const char *path      = argv[1];
	const char *keytofind = argv[2];

	hm_dir_t dir_real;

	hm_dir_t *dir = hm_dir_open(& dir_real, path);
	dir_open_test(dir, keytofind);

	hm_dir_reopen(dir);
	dir_open_test(dir, keytofind);

	hm_dir_close(dir);

	return 0;
}
