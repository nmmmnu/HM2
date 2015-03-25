#include "hm_pair.h"
#include "hm_dir.h"

#include <stdio.h>
#include <stdlib.h>	// NULL

static void _print_pair(const hm_pair_t *pair)
{
	const int only = 1;

	if (pair && only){
		hm_pair_printf(pair);
	}else if (pair){
		printf("Pair is %s\n", hm_pair_valid(pair, NULL) ? "valid" : "invalid" );
		printf("Pair checksum is %s\n", hm_pair_checksumvalid(pair) ? "valid" : "invalid" );
		printf("---begin---\n");
		hm_pair_printf(pair);
		printf("----end----\n");
	}else{
		printf("Not Found\n");
	}
}

static int find_in_dir(const char *path, const char *keytofind)
{
	hm_dir_t *dir = hm_dir_opena(path);

	const hm_pair_t *pair = hm_dir_get(dir, keytofind);

	_print_pair(pair);

	hm_dir_close(dir);
	free(dir);

	return 0;
}

static int list_dir(const char *path)
{
	hm_dir_t *dir = hm_dir_opena(path);

	hm_dir_printf(dir);

	hm_dir_close(dir);
	free(dir);

	return 0;
}

static int dump_dir(const char *path)
{
	const uint64_t count = 30;

	hm_dir_t *dir = hm_dir_opena(path);

	hm_dir_it_t *it = hm_dir_it_open(dir);

	const hm_pair_t *pair;
	uint64_t i = 0;
	for(pair = hm_dir_it_first(it); pair; pair = hm_dir_it_next(it)){
		_print_pair(pair);

		++i;

		if (i >= count)
			break;
	}

	hm_dir_it_close(it);

	hm_dir_close(dir);
	free(dir);

	return 0;
}

int main(int argc, char **argv)
{
	if (argc > 2){

		if (argc == 4 && strcmp("find", argv[1]) == 0)
			return find_in_dir(argv[2], argv[3]);

		if (argc == 3 && strcmp("dump", argv[1]) == 0)
			return dump_dir(argv[2]);

		if (argc == 3 && strcmp("list", argv[1]) == 0)
			return list_dir(argv[2]);
	}

	printf("Usage:\n");
	printf("\t%s list [directory] - list files in the database\n", argv[0]);
	printf("\t%s find [directory] [key] - find in the database\n", argv[0]);
	printf("\t%s dump [directory] - dump the database\n", argv[0]);
	printf("\t\tDo not forget about quotes around the directory\n");

	return 1;
}
