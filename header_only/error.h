#ifndef STEEL_ERROR_H_
#define STEEL_ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define Steel_Error(fmt, ...)								\
	do {													\
		fprintf(stderr, "error: %s\n", fmt, ##__VA_ARGS__);	\
		exit(EXIT_FAILURE);									\
	} while (0)

#define Steel_MallocError Steel_Error("memory allocation failed")

#endif // STEEL_ERROR_H_
