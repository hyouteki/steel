#ifndef STEEL_LL_H_
#define STEEL_LL_H_

#include <stdlib.h>
#include "node.h"
#include "error.h"

typedef struct Steel_LL {
	Steel_Node *head;
	Steel_Node *tail;
	size_t size;
} Steel_LL;

Steel_LL *Steel_LL_Init();
void Steel_LL_PushBack(Steel_LL *ll, void *data, size_t data_size);
void Steel_LL_PopFront(Steel_LL *ll);
void Steel_LL_Free(Steel_LL *ll);

#define Steel_LL_Empty(ll) (ll->head == NULL)
#define Steel_LL_Head(ll) (ll->head)
#define Steel_LL_Front(ll) (Steel_LL_Empty(ll)? NULL: ll->head->data)
#define Steel_LL_Back(ll) (Steel_LL_Empty(ll)? NULL: ll->tail->data)
#define Steel_LL_Size(ll) (ll->size)

Steel_LL *Steel_LL_Init() {
	Steel_LL *ll = (Steel_LL *)malloc(sizeof(Steel_LL));
	if (!ll) Steel_MallocError;
	ll->head = NULL;
	ll->tail = NULL;
	ll->size = 0;
	return ll;
}

void Steel_LL_PushBack(Steel_LL *ll, void *data, size_t data_size) {
	Steel_Node *new_tail = Steel_Node_Init(data, data_size);
	if (ll->head == NULL) {
		ll->head = new_tail;
		ll->tail = new_tail;
		return;
	}
	ll->tail->next = new_tail;
	ll->tail = ll->tail->next;
	ll->size++;
}

void Steel_LL_PopFront(Steel_LL *ll) {
	if (!ll->head) return;
	Steel_Node *next = ll->head->next;
	if (ll->head == ll->tail) ll->tail = NULL;
	Steel_Node_Free(ll->head);
	ll->head = next;
	ll->size--;
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
