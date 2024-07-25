#include "../stack.h"

int main() {
	int n1 = 1, n2 = 2, n3 = 3, n4 = 4;
	Steel_Stack *stack = Steel_Stack_Init();
	Steel_Stack_Push(stack, &n1, sizeof(int));
	Steel_Stack_Push(stack, &n2, sizeof(int));
	Steel_Stack_Pop(stack);
	Steel_Stack_Push(stack, &n2, sizeof(int));
	Steel_Stack_Push(stack, &n3, sizeof(int));
	Steel_Stack_Push(stack, &n4, sizeof(int));
	Steel_Stack_Pop(stack);
	
	while (!Steel_Stack_Empty(stack)) {
		printf("top: %d\n", *(int *)Steel_Stack_Peek(stack));
		Steel_Stack_Pop(stack);
	}
	Steel_Stack_Free(stack);

	return 0;
}
