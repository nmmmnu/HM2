// Create pair

inline static hm_pair_t *hm_pair_createn(const char*key, const char*val, hm_valsize_t vallen){
	return hm_pair_createnx(key, val, vallen, 0);
}

inline static hm_pair_t *hm_pair_createx(const char *key, const char *val, uint32_t expires){
	hm_valsize_t vallen = val == NULL ? 0 : strlen(val);
	return hm_pair_createnx(key, val, vallen, expires);
}

inline static hm_pair_t *hm_pair_create(const char*key, const char*val){
	return hm_pair_createx(key, val, 0);
}

inline static hm_pair_t *hm_pair_createtombstone(const char*key){
	return hm_pair_create(key, NULL);
}

inline static void hm_pair_free(hm_pair_t *pair){
	free(pair);
}

// sizeof

inline static size_t hm_pair_sizeof(const hm_pair_t *pair){
	return sizeof(hm_pair_t) + be16toh(pair->keylen) + 1 + be32toh(pair->vallen) + 1;
}

// Get key and value

inline static const char *hm_pair_getkey(const hm_pair_t *pair){
	return & pair->buffer[0];
}

inline static const char *hm_pair_getval(const hm_pair_t *pair){
	return pair->vallen ? & pair->buffer[ be16toh(pair->keylen) + 1 ] : NULL;
}

// Cmp functions

inline static int hm_pair_cmpkey(const hm_pair_t *pair, const char *key){
	return key == NULL ? -1 : strcmp(hm_pair_getkey(pair), key);
}

inline static int hm_pair_cmppair(const hm_pair_t *pair1, const hm_pair_t *pair2){
	return strcmp(hm_pair_getkey(pair1), hm_pair_getkey(pair2));
}

// Misc functions

#ifdef HM_PAIR_EXPIRATION
#else
inline static int hm_pair_valid(const hm_pair_t *pair1, const hm_pair_t *pair2){
	return 1;
}
#endif

#ifdef HM_PAIR_CHECKSUM
#else
inline static void hm_pair_checksummake(const hm_pair_t *pair){
	/* noop */
}
inline static int hm_pair_checksumvalid(const hm_pair_t *pair){
	return 1;
}
#endif



