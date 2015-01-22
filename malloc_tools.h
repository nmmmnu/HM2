#ifndef _MALLOC_TOOLS_H
#define _MALLOC_TOOLS_H

#include <stdlib.h>
#include <stdio.h>

#define MC_ALIGN	(sizeof(size_t) * 2)
#define MC_OVERHEAD	sizeof(size_t)

inline static size_t xmalloc_calc(size_t size){
	size_t newsize = size / MC_ALIGN;

	if (size % MC_ALIGN)
		newsize++;

	return newsize * MC_ALIGN + MC_OVERHEAD;
}

inline static void *xmalloc(size_t size){
	static size_t malloc_total_mem      = 0;
	static size_t malloc_total_memalign = 0;
	static size_t malloc_total_call     = 0;

	malloc_total_memalign += xmalloc_calc(size);
	malloc_total_mem += size;
	malloc_total_call++;

	//printf("MSIZE:%10zu:%10zu\n", size, xmalloc_calc(size));

	if ((malloc_total_call % 10000) == 0){
		printf("MALLOC TOOLS: malloc calls %12zu, allocated %12zu bytes (%12zu bytes aligned with overhead)\n",
			malloc_total_call,
			malloc_total_mem,
			malloc_total_memalign
		);
	}

	return malloc(size);
}

#endif
