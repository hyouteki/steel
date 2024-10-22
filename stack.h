#ifndef STEEL_STACK_H_
#define STEEL_STACK_H_

#include <stdlib.h>
#include "node.h"
#include "error.h"

typedef struct Steel_Stack {
	Steel_Node *top;
	size_t size;
} Steel_Stack;

Steel_Stack *Steel_Stack_Init();
void Steel_Stack_Push(Steel_Stack *stack, void *data, size_t data_size);
void Steel_Stack_Pop(Steel_Stack *stack);
void Steel_Stack_PopNotFree(Steel_Stack *stack);
void Steel_Stack_Free(Steel_Stack *stack);

#define Steel_Stack_Empty(stack) (stack->top == NULL)
#define Steel_Stack_Top(stack) (stack->top->data)
#define Steel_Stack_Peek(stack) (stack->top)
#define Steel_Stack_Size(stack) (stack->size)

Steel_Stack *Steel_Stack_Init() {
	Steel_Stack *stack = (Steel_Stack *)malloc(sizeof(Steel_Stack));
	if (!stack) Steel_MallocError;
	stack->top = NULL;
	stack->size = 0;
	return stack;
}

void Steel_Stack_Push(Steel_Stack *stack, void *data, size_t data_size) {
	Steel_Node *new_top = Steel_Node_Init(data, data_size);
	new_top->next = stack->top;
	stack->top = new_top;
	stack->size++;
}

void Steel_Stack_Pop(Steel_Stack *stack) {
	if (Steel_Stack_Empty(stack)) return;
	Steel_Node *new_top = stack->top->next;
	Steel_Node_Free(stack->top);
	stack->top = new_top;
	stack->size--;
}

void Steel_Stack_PopNotFree(Steel_Stack *stack) {
	if (Steel_Stack_Empty(stack)) return;
	stack->top = stack->top->next;
	stack->size--;
}

void Steel_Stack_Free(Steel_Stack *stack) {
	if (!stack) return;
	Steel_Node *itr = stack->top;
	while (itr) {
		Steel_Node *next = itr->next;
		Steel_Node_Free(itr);
		itr = next;
	}
	free(stack);
}

#endif // STEEL_STACK_H_
