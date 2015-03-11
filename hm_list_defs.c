#include "hm_list_defs.h"

#include "hm_pair.h"

int _hm_file_fwrite_junk(FILE *F, size_t count){
	uint64_t be = 0xdeedbeef;

	size_t i;
	for(i = 0; i < count; i++)
		fwrite(& be, sizeof(uint64_t), 1, F);

	return 0;
}
