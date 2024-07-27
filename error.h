#ifndef STEEL_ERROR_H_
#define STEEL_ERROR_H_

#include <stdio.h>
#include <stdlib.h>

#define Steel_Error(message) ({fprintf(stderr, "error: %s\n", message);	\
			exit(EXIT_FAILURE);})

#define Steel_MallocError (Steel_Error("memory allocation failed"))

#endif // STEEL_ERROR_H_
