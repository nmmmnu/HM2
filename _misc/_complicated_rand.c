
inline static unsigned char __hm_skiplist_height_init(){
	unsigned char bits = 0;
	int m = RAND_MAX;

	while(m & 0x1){
		m = m >> 1;
		bits++;
	}

	return bits;
}

static unsigned char __hm_skiplist_height(unsigned char max){
	static unsigned char bits = 0;
	if (!bits)
		bits = __hm_skiplist_height_init();

	unsigned char h = 1;

	int r = 0;
	int m = 0;

	for(;;){
		if (h >= max)
			break;

		if (m == 0){
			r = rand();
			m = bits;
		}

		if ( (r & 0x1) == 0 )
			break;

		h++;

		r = r >> 1;
	}

	return h;
}

inline static unsigned char _hm_skiplist_height(const hm_skiplist_t *l){
	return __hm_skiplist_height(l->height);
}

