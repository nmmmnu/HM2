#include "hm_pair.h"
#include "hm_vector.h"

#include "malloc_info.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>	// sleep
#include <stdlib.h>	// free



#define PRINTF_TEST(module, test, func) \
	printf( "%-15s Testing %-20s %s\n", module, test, func ? "OK" : "Fail")



void hm_pair_test(const int delay){
	const char *key = "aaancdefgh";
	const char *val = "1234567890";

	hm_pair_t *p1 = hm_pair_create(key, val);
	hm_pair_t *p2 = hm_pair_createx(key, val, 1);

	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, key) == 0			);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "~~~ non existent") < 0	);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "!!! non existent") > 0	);

	PRINTF_TEST("hm_pair_t", "key",		strcmp(hm_pair_getkey(p1), key) == 0		);
	PRINTF_TEST("hm_pair_t", "val",		strcmp(hm_pair_getval(p1), val) == 0		);


	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p1)				);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2)				);

	if (delay){
	printf("sleep for 1 sec...\n");
	sleep(1);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p1)				);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2) == 0				);
	}

	free(p1);
	free(p2);
}



static hm_vector_t *_hm_vector_populate(hm_vector_t *v){
	// go to empty list
	hm_vector_put(v, hm_pair_create("3 city", "Sofia")		);
	// go first
	hm_vector_put(v, hm_pair_create("1 name", "Niki")		);
	// go middle
	hm_vector_put(v, hm_pair_create("2 age", "22")			);
	// go last
	hm_vector_put(v, hm_pair_create("4 os", "Linux")		);

	return v;
}

static void _hm_vector_test_overwrite(hm_vector_t *v){
	_hm_vector_populate(v);

	hm_vector_put(v, hm_pair_create("2 val", "original")	);
	hm_vector_put(v, hm_pair_create("2 val", "overwritten")	);

	const hm_pair_t *p = hm_vector_get(v,"2 val");
	PRINTF_TEST("hm_vector_t", "overwrite",	! strcmp(hm_pair_getval(p), "overwritten")	);

	hm_vector_free(v);
}

static void _hm_vector_test_remove(hm_vector_t *v){
	_hm_vector_populate(v);

	// remove middle
	hm_vector_remove(v, "2 age");
	// remove first
	hm_vector_remove(v, "1 name");
	// remove middle
	hm_vector_remove(v, "4 os");

	const hm_pair_t *p = hm_vector_get(v,"3 city");
	PRINTF_TEST("hm_vector_t", "remove",	! strcmp(hm_pair_getval(p), "Sofia")	);
	PRINTF_TEST("hm_vector_t", "remove",	hm_vector_count(v) == 1			);

	// remove last
	hm_vector_remove(v, "3 city");

	PRINTF_TEST("hm_vector_t", "remove",	hm_vector_count(v) == 0			);

	hm_vector_free(v);
}

void hm_vector_test(){
	hm_vector_t v_real;
	hm_vector_t *v = hm_vector_create(& v_real);

	_hm_vector_populate(v);
	hm_vector_dump(v);
	hm_vector_free(v);

	PRINTF_TEST("hm_vector_t", "put",	1		);
	PRINTF_TEST("hm_vector_t", "free",	1		);

	_hm_vector_test_overwrite(v);
	_hm_vector_test_remove(v);
}




int main(int argc, char **argv){
	hm_pair_test(argc > 1);

	hm_vector_test();



	display_mallinfo(0);

	return 0;
}

