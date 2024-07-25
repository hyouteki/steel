#ifndef STEEL_LL_H_
#define STEEL_LL_H_

#include <stdlib.h>
#include "node.h"
#include "error.h"

typedef struct Steel_LL {
	Steel_Node *head;
	Steel_Node *tail;
} Steel_LL;

Steel_LL *Steel_LL_Init();
void Steel_LL_Push(Steel_LL *ll, void *data, size_t data_size);
void Steel_LL_Free(Steel_LL *ll);

#define Steel_LL_Empty(ll) (ll->head == NULL)

Steel_LL *Steel_LL_Init() {
	Steel_LL *ll = (Steel_LL *)malloc(sizeof(Steel_LL));
	if (!ll) MallocError;
	ll->head = NULL;
	ll->tail = NULL;
	return ll;
}

void Steel_LL_Push(Steel_LL *ll, void *data, size_t data_size) {
	Steel_Node *new_tail = Steel_Node_Init(data, data_size);
	if (ll->head == NULL) {
		ll->head = new_tail;
		ll->tail = new_tail;
		return;
	}
	ll->tail->next = new_tail;
	ll->tail = ll->tail->next;
}

void Steel_LL_Free(Steel_LL *ll) {
	if (!ll) return;
	Steel_Node *itr = ll->head;
	while (itr) {
		Steel_Node *next = itr->next;
		Steel_Node_Free(itr);
		itr = next;
	}
	free(ll);
}

#endif // STEEL_LL_H_
