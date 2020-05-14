#ifndef __QUEUE_ARRAY_H__
#define __QUEUE_ARRAY_H__

#define TYPE_1 1
#define TYPE_2 2

#include <stdio.h>
#include <errno.h>

#include "structs.h"
#include "errors.h"

int addToTailArray(queueArrayType *const queue, const int type);

int removeFromHeadArray(queueArrayType *const queue);

#endif