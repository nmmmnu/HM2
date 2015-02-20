#include <stdio.h>
#include <stdint.h>

typedef struct _test_t{

	uint64_t	created;	// 8
	uint32_t	expires;	// 4

	uint32_t	vallen;		// 4
	uint16_t	keylen;		// 2

	char		checksum;	// 1
}  test_t;
//__attribute__((__packed__))

int main(){
	test_t x = {
		.created	= 0x1111111122222222,
		.expires	= 0xEEEEEEEE,
		.vallen		= 0xAAAAAAAA,
		.keylen		= 0xEEEE,
		.checksum	= 0xCC
	};

	const char *s = (const char *) & x;

	unsigned i;
	for(i = 0; i < sizeof(x); i++)
		printf("%3u %x\n", i, 0xFF & s[i]);

	return 0;
}


