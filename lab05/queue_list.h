#ifndef __QUEUE_LIST_H__
#define __QUEUE_LIST_H__

#define TYPE_1 1
#define TYPE_2 2

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "structs.h"
#include "errors.h"

int addToTailList(queueType *queue, const int type, const int timing);

int removeFromHeadList(queueType *const queue);

void freeList(queueType *const queue);

#endif