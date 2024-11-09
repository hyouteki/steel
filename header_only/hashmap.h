#ifndef STEEL_HASHMAP_H_
#define STEEL_HASHMAP_H_

#include <stdlib.h>
#include <string.h>

// STEEL_HASH_H_ starts here
unsigned int Steel_Hash_SDBM(void *key);
// Reference: http://www.cse.yorku.ca/~oz/hash.html#sdbm
unsigned int Steel_Hash_SDBM(void *key) {
	char *data = (char *)key;
	unsigned long long hash = 0;
	for (unsigned int i = 0; i < strlen(data); ++i)
		hash = data[i] + (hash<<6) + (hash<<16) - hash;
	return hash;
}
// STEEL_HASH_H_ ends here

// STEEL_ERROR_H_ starts here
#include <stdio.h>
#define Steel_Error(fmt, ...)								\
	do {													\
		fprintf(stderr, "error: %s\n", fmt, ##__VA_ARGS__);	\
		exit(EXIT_FAILURE);									\
	} while (0)
#define Steel_MallocError Steel_Error("memory allocation failed")
// STEEL_ERROR_H_ ends here

#define Steel_Hashmap_Size 4096

typedef struct Steel_Hashmap_Entry {
	void *key;
	void *value;
	struct Steel_Hashmap_Entry *next;
} Steel_Hashmap_Entry;

typedef struct Steel_Hashmap {
	Steel_Hashmap_Entry *table[Steel_Hashmap_Size];
	unsigned int (*HashKey)(void *key);
	void *(*DupKey)(void *key);
	void *(*DupValue)(void *value);
	int (*CmpKey)(void *key1, void *key2);
} Steel_Hashmap;

Steel_Hashmap *Steel_Hashmap_Init();
void Steel_Hashmap_Insert(Steel_Hashmap *hashmap, void *key, void *value);
int Steel_Hashmap_Find(Steel_Hashmap *, void *);
void *Steel_Hashmap_Lookup(Steel_Hashmap *, void *);
void Steel_Hashmap_Free(Steel_Hashmap *hashmap);

static void *steel_dup_string(void *data) {
	return (void *)strdup((char *)data);
}

static int steel_str_cmp(void *s1, void *s2) {
	return strcmp((char *)s1, (char *)s2);
}

Steel_Hashmap *Steel_Hashmap_Init() {
	Steel_Hashmap *hashmap = (Steel_Hashmap *)malloc(sizeof(Steel_Hashmap));
	if (!hashmap) Steel_MallocError;
	hashmap->HashKey = &Steel_Hash_SDBM;
	hashmap->DupKey = &steel_dup_string;
	hashmap->DupValue = &steel_dup_string;
	hashmap->CmpKey = &steel_str_cmp;
	return hashmap;
}

// This will create a copy of key and value
void Steel_Hashmap_Insert(Steel_Hashmap *hashmap, void *key, void *value) {
	unsigned int hash = hashmap->HashKey(key)%Steel_Hashmap_Size;
	Steel_Hashmap_Entry *entry = (Steel_Hashmap_Entry *)malloc(sizeof(Steel_Hashmap_Entry));
	if (!entry) Steel_MallocError;
    entry->key = hashmap->DupKey(key);
    entry->value = hashmap->DupValue(value);
	entry->next = hashmap->table[hash];
    hashmap->table[hash] = entry;
}

int Steel_Hashmap_Find(Steel_Hashmap *hashmap, void *key) {
	unsigned int hash = hashmap->HashKey(key)%Steel_Hashmap_Size;
	Steel_Hashmap_Entry *itr = hashmap->table[hash];
	while (itr) {
		if (hashmap->CmpKey(itr->key, key) == 0) return 1;
		itr = itr->next;
	}
	return 0;
}

void *Steel_Hashmap_Lookup(Steel_Hashmap *hashmap, void *key) {
    unsigned int hash = hashmap->HashKey(key)%Steel_Hashmap_Size;
	Steel_Hashmap_Entry *itr = hashmap->table[hash];
	while (itr) {
		if (hashmap->CmpKey(itr->key, key) == 0)
			return hashmap->DupValue(itr->value);
		itr = itr->next;
	}
	return NULL;
}

void Steel_Hashmap_Free(Steel_Hashmap *hashmap) {
    if (!hashmap) return;
    for (size_t i = 0; i < Steel_Hashmap_Size; ++i) {
        Steel_Hashmap_Entry *entry = hashmap->table[i];
        while (entry) {
            Steel_Hashmap_Entry *next = entry->next;
            free(entry->key);
            free(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(hashmap);
}

#endif // STEEL_HASHMAP_H_
