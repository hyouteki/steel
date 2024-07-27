#include "../ll.h"

int main() {
	int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
	Steel_LL *ll = Steel_LL_Init();
	Steel_LL_PushBack(ll, &n1, sizeof(int));
	Steel_LL_PushBack(ll, &n2, sizeof(int));
	Steel_LL_PushBack(ll, &n3, sizeof(int));
	Steel_LL_PushBack(ll, &n4, sizeof(int));

	Steel_Node *itr = ll->head;
	while (itr) {
		printf("node: %d\n", *(int *)itr->data);
		itr = itr->next;
	}
	Steel_LL_Free(ll);

	return 0;
}
