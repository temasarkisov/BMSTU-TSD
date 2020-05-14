#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <time.h>

#include "structs.h"
#include "errors.h"
#include "queue_array.h"
#include "queue_list.h"
#include "results.h"

#define TOTAL_CYCLED 1000

#define DOWN_LIMIT_ARRIVAL_1 0 
#define UP_LIMIT_ARRIVAL_1 5
#define DOWN_LIMIT_CYCLING_1 0 
#define UP_LIMIT_CYCLING_1 4
#define DOWN_LIMIT_CYCLING_2 0 
#define UP_LIMIT_CYCLING_2 4

double setTime(float downLimit, float upLimit);

void plusTiming(queueArrayType *const timing);

int doModelingArray(queueArrayType *const queue, queueArrayType *const timing, rangeType *const range,\
                      infoType *const info, int *const maxSizeState,  clock_t *const ticksTime);

int inputRanges(FILE *const inStream, FILE *const outStream, rangeType *const data);

void setDefault(rangeType *const data);

void plusTimingList(queueType *const queue);

int doModelingList(queueType *const queue, rangeType *const range, infoType *const info, int *const maxSizeState, clock_t *const ticksTime);



#endif