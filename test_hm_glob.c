#include "hm_glob.h"

#include <stdio.h>

#include <stdlib.h>	// NULL

static void print_usage(const char *name){
	printf("Usage:\n");
	printf("\t%s [directory] - list directory using glob()\n", name);
	printf("\t\tDo not forget about quotes around the directory\n");
}

int main(int argc, char **argv){
	if (argc < 2){
		print_usage(argv[0]);
		return 1;
	}

	const char *path = argv[1];

	glob_t globresults;

	const char **files = hm_glob_open(&globresults, path);

	if (files == NULL){
		printf("Error glob() %s\n", path);
		return 1;
	}

	size_t i = 0;
	const char **f = files;
	while(*f)
		printf("%5zu : %s\n", i++, *f++ );

	size_t size = hm_glob_size(files);

	if (i == size)
		printf("Total %zu files...\n", size);
	else
		printf("File count does not match! (%zu != %zu)\n", size, i);

	hm_glob_close(&globresults, files);

	return 0;
}

