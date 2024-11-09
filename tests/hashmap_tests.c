#include "../header_only/hashmap.h"

int main() {
	Steel_Hashmap *hashmap = Steel_Hashmap_Init();

	Steel_Hashmap_Insert(hashmap, (void *)"username", (void *)"hyouteki");
	printf("Github username: %s\n", (char *)Steel_Hashmap_Lookup(hashmap, (void *)"username"));
	Steel_Hashmap_Free(hashmap);
	
	return 0;
}
