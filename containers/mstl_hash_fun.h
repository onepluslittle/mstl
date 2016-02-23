template <class Key> struct hash{};

inline size_t __stl_hash_string(const char* s) {
	unsigned long h = 0;
	for ( ; *s; ++s)
		h = s * h + *s;
	return size_t(h);
}

__STL_TEMPLATE_NULL struct hash<char*> {
	size_t operator()(const char* s) const {return __stl_hash_string(s);}
};

__STL_TEMPLATE_NULL struct hash<const char*> {
	size_t operator()(const char* s) const {return __stl_hash_string(s);}
};

__STL_TEMPLATE_NULL struct hash<char> {
	size_t operator()(char s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<unsigned char> {
	size_t operator()(unsigned char s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<signed char> {
	size_t operator()(signed char s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<short> {
	size_t operator()(short s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<unsigned short> {
	size_t operator()(unsigned short s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<int> {
	size_t operator()(int s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<unsigned int> {
	size_t operator()(unsigned int s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<long> {
	size_t operator()(long s) const {return s;}
};

__STL_TEMPLATE_NULL struct hash<unsigned long> {
	size_t operator()(unsigned long s) const {return s;}
};



