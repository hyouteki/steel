#ifndef STEEL_HASH_H_
#define STEEL_HASH_H_

#include <string.h>

unsigned int Steel_Hash_SDBM(void *key);

// Reference: http://www.cse.yorku.ca/~oz/hash.html#sdbm
unsigned int Steel_Hash_SDBM(void *key) {
	char *data = (char *)key;
	unsigned long long hash = 0;
	for (unsigned int i = 0; i < strlen(data); ++i)
		hash = data[i] + (hash<<6) + (hash<<16) - hash;
	return hash;
}

#endif // STEEL_HASH_H_
