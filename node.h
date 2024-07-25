#ifndef STEEL_NODE_H_
#define STEEL_NODE_H_

#include <stdlib.h>
#include "error.h"
#include "string.h"

typedef struct Steel_Node {
	void *data;
	size_t data_size;
	struct Steel_Node *next;
} Steel_Node;

Steel_Node *Steel_Node_Init(void *data, size_t data_size);
Steel_Node *Steel_Node_Dup(Steel_Node *other);
void Steel_Node_Free(Steel_Node *node);

Steel_Node *Steel_Node_Init(void *data, size_t data_size) {
	Steel_Node *node = (Steel_Node *)malloc(sizeof(Steel_Node));
	if (!node) MallocError;
	node->data = (void *)malloc(data_size);
	if (!node->data) {
		free(node);
		MallocError;
	}
	memcpy(node->data, data, data_size);
	node->data_size = data_size;
	node->next = NULL;
	return node;
}

Steel_Node *Steel_Node_Dup(Steel_Node *other) {
	Steel_Node *node = (Steel_Node *)malloc(sizeof(Steel_Node));
	if (!node) MallocError;
	node->data = (void *)malloc(other->data_size);
	if (!node->data) {
		free(node);
		MallocError;
	}
	memcpy(node->data, other->data, other->data_size);
	node->data_size = other->data_size;
	node->next = NULL;
	return node;
}

void Steel_Node_Free(Steel_Node *node) {
	if (!node) return;
	free(node->data);
	free(node);
}

#endif // STEEL_NODE_H_
