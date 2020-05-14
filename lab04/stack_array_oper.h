#ifndef __STACK_ARRAY_OPER_H__
#define __STACK_ARRAY_OPER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs_t.h"
#include "errno.h"
#include "word_oper.h"

/* int stackArrayAllocate(stackArray_t *stackArray, const int stackMaxSize); */

int stackArrayPush(stackArray_t *stackArray, const int stackMaxSize, char *const wordNew);

int stackArrayPop(stackArray_t *const stackArray);

void stackArrayPrint(stackArray_t const stackArray);

void stackArrayCondition(stackArray_t const stackArray, const int stackMaxSize);

#endif