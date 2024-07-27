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
void Steel_Node_Free(Steel_Node *node);

#define Steel_Node_Next(node) (node = node? node->next: NULL)

Steel_Node *Steel_Node_Init(void *data, size_t data_size) {
	Steel_Node *node = (Steel_Node *)malloc(sizeof(Steel_Node));
	if (!node) Steel_MallocError;
	node->data = (void *)malloc(data_size);
	if (!node->data) {
		free(node);
		Steel_MallocError;
	}
	memcpy(node->data, data, data_size);
	node->data_size = data_size;
	node->next = NULL;
	return node;
}

void Steel_Node_Free(Steel_Node *node) {
	if (!node) return;
	free(node->data);
	free(node);
}

#endif // STEEL_NODE_H_
