#ifndef __STACK_LIST_OPER_H__
#define __STACK_LIST_OPER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structs_t.h"
#include "errno.h"
#include "word_oper.h"

int stackListPush(stackListNode_t **stackListNode, char *const wordNew);

int stackListPop(stackListNode_t **stackListNode, stackListNode_t **stackListNodeFreed);

void stackListPrint(stackListNode_t *stackListNode);

void stackListCondition(stackListNode_t *stackListNode, stackListNode_t *stackListNodeFreed);

#endif