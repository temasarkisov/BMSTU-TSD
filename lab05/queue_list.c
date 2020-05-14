#include "queue_list.h"

int addToTailList(queueType *queue, const int type, const int timing)
{
    listType *node = NULL; 
    listType *copy = queue->head;

    if ((node = malloc(sizeof(listType))) == NULL)
    {
        errno = MEM_NOT_ALLOCED;
        return ERROR;
    }

    node->type = type;
    node->waitingTime = timing;
    node->next = NULL;

    if (copy)
    {
        while (copy->next)
        {
            copy = copy->next;
        }

        copy->next = node; 
    }
    else
    {
        queue->head = node;
    }
    
    (queue->size)++;
    return OK;
}

int removeFromHeadList(queueType *const queue)
{
    listType *copy = queue->head;
    listType *node = NULL;
    int type = 0;

    type = copy->type;
    queue->head = copy->next;
    free(copy);
    (queue->size)--;

    if (type == TYPE_2)
    {
        if (queue->size < 4)
        {
            addToTailList(queue, TYPE_2, 0);
        }
        else
        {
            copy = queue->head;

            for (int i = 0; i < 2; i++)
            {
                copy = copy->next;
            }

            if ((node = malloc(sizeof(listType))) == NULL)
            {
                errno = MEM_NOT_ALLOCED;
                return ERROR;
            }

            node->waitingTime = 0;
            node->type = TYPE_2;
            node->next = copy->next;
            copy->next = node;
            (queue->size)++;
        }
    }

    return OK;
}

void freeList(queueType *const queue)
{
    listType *copy_head = queue->head;
    listType *local = NULL;

    while (copy_head)
    {
        local = copy_head;
        copy_head = copy_head->next;
        free(local);
    }
}