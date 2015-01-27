#include "test_hm_factory.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>	// sleep



#define PRINTF_TEST(module, test, func) \
	printf( "%-15s Testing %-20s %s\n", module, test, func ? "OK" : "Fail")



void hm_pair_test(const int delay){
	const char *key = "aaancdefgh";
	const char *val = "1234567890";

	hm_pair_t *p1 = hm_pair_create(key, val);
#ifdef HM_PAIR_EXPIRATION
	hm_pair_t *p2 = hm_pair_createx(key, val, 1);
#endif

	hm_pair_t *p3 = hm_pair_createtombstone(key);

	PRINTF_TEST("hm_pair_t", "tombstone",	hm_pair_getval(p3) == NULL			);

	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, key) == 0			);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "~~~ non existent") < 0	);
	PRINTF_TEST("hm_pair_t", "cmp",		hm_pair_cmpkey(p1, "!!! non existent") > 0	);

	PRINTF_TEST("hm_pair_t", "key",		strcmp(hm_pair_getkey(p1), key) == 0		);
	PRINTF_TEST("hm_pair_t", "val",		strcmp(hm_pair_getval(p1), val) == 0		);

	// these always pass
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p1, NULL)				);
	PRINTF_TEST("hm_pair_t", "checksum",	hm_pair_checksumvalid(p1)			);

#ifdef HM_PAIR_CHECKSUM
	// corrupt p1
	p1->keylen--;
	PRINTF_TEST("hm_pair_t", "checksum",	! hm_pair_checksumvalid(p1)			);
#endif

#ifdef HM_PAIR_EXPIRATION
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2, NULL)				);
	if (delay){
	printf("sleep for 1 sec...\n");
	sleep(1);
	PRINTF_TEST("hm_pair_t", "valid",	hm_pair_valid(p2, NULL) == 0			);
	}
#endif

	hm_pair_free(p1);
#ifdef HM_PAIR_EXPIRATION
	hm_pair_free(p2);
#endif
	hm_pair_free(p3);
}



static size_t _hm_list_populate(hm_list_t *v){
	hm_list_removeall(v);

	void *p;
	size_t size = 0;

	// go to empty list
	p = hm_pair_create("3 city", "Sofia");	size += hm_pair_sizeof(p);	hm_list_put(v, p);
	// go first
	p = hm_pair_create("1 name", "Niki");	size += hm_pair_sizeof(p);	hm_list_put(v, p);
	// go middle
	p = hm_pair_create("2 age", "22");	size += hm_pair_sizeof(p);	hm_list_put(v, p);
	// go last
	p = hm_pair_create("4 os", "Linux");	size += hm_pair_sizeof(p);	hm_list_put(v, p);

	return size;
}

static void _hm_list_test_overwrite(hm_list_t *v){
	_hm_list_populate(v);

	const char *overwr = "overwritten";

	hm_list_put(v, hm_pair_create("2 val", "original")	);
	hm_list_put(v, hm_pair_create("2 val", overwr)	);

	const hm_pair_t *p = hm_list_get(v,"2 val");
	PRINTF_TEST("hm_list_t", "overwrite",	! strcmp(hm_pair_getval(p), overwr)	);
}

static void _hm_list_test_remove(hm_list_t *v){
	_hm_list_populate(v);

	// remove middle
	hm_list_remove(v, "2 age");
	// remove first
	hm_list_remove(v, "1 name");
	// remove middle
	hm_list_remove(v, "4 os");

	const hm_pair_t *p = hm_list_get(v,"3 city");
	PRINTF_TEST("hm_list_t", "remove",	! strcmp(hm_pair_getval(p), "Sofia")	);
	PRINTF_TEST("hm_list_t", "remove",	hm_list_count(v) == 1			);

	// remove last
	hm_list_remove(v, "3 city");

	PRINTF_TEST("hm_list_t", "remove",	hm_list_count(v) == 0			);
}

static void _hm_list_test_dump(hm_list_t *v){
	size_t size = _hm_list_populate(v);

	hm_list_printf(v, 0);

	PRINTF_TEST("hm_list_t", "sizeof",	hm_list_sizeof(v) == size		);
	PRINTF_TEST("hm_list_t", "put",		1					);
	PRINTF_TEST("hm_list_t", "free",	1					);
}

void hm_list_test(){
	hm_list_t *v = _list_factory();

	_hm_list_test_dump(v);
	_hm_list_test_overwrite(v);
	_hm_list_test_remove(v);

	hm_list_destroy(v);
}

void print_sizes(){
	const char *format = "sizeof(%-10s) = %5zu\n";

	printf(format, "hm_pair_t", sizeof(hm_pair_t));
	printf(format, "hm_list_t", sizeof(hm_list_t));
}


int main(int argc, char **argv){
	hm_pair_test(argc > 1);

	hm_list_test();

	print_sizes();

	return 0;
}

