#include "queue_array.h"

int addToTailArray(queueArrayType *const queue, const int type)
{
    if (queue->tail == queue->downLimit)
    {
        errno = QUEUE_REFILLED;
        return ERROR;
    }
    
    *(queue->tail) = type;
    (queue->tail)--;
    return OK;
}

int removeFromHeadArray(queueArrayType *const queue)
{
    int type = 0;

    if (queue->tail == queue->head)
    {
        errno = QUEUE_IS_EMPTY;
        return ERROR;
    }

    type = *(queue->head); 

    for (int *p = queue->head; p > queue->tail + 1; p--)
    {
        *(p) = *(p - 1);
    }

    (queue->tail)++;

    if (type == TYPE_2)
    {
        if (queue->head - (queue->tail + 1) < 3)
        {
            addToTailArray(queue, TYPE_2);
        }
        else
        {
            for (int *p = (queue->tail + 1) - 1; p < (queue->head) - 3; p++)
            {
                *(p) = *(p + 1);
            }

            *((queue->head) - 3) = TYPE_2;
            (queue->tail)--;
        }
    }

    return OK;
}