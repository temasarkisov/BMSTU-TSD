#include "stats.h"

double timeStackArrayOperations()
{
    stackArray_t stackArray;
    //stackArray.wordsArray = (char **) malloc(1000 * sizeof(char *));

    clock_t begin = clock();
    for (int i = 0; i < 1000; i++)
    {
        stackArrayPush(&stackArray, 1000, "testtest");
        stackArrayPop(&stackArray);
    }
    clock_t end = clock();
    
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n\tВремя выполнения операций (реализация стека массивом)  -  %lf\n", timeSpent);
    printf("\tКоличество памяти (реализация стека массивом)  -  %lu\n\n", 1000 * sizeof(char*) + sizeof(int));
    return timeSpent;
}

double timeStackListOperations()
{
    stackListNode_t *stackListNodeHead = NULL;
    stackListNode_t *stackListNodeFreed = NULL;
    
    clock_t begin = clock();
    for (int i = 0; i < 1000; i++)
    {
        stackListPush(&stackListNodeHead, "testtest");
        stackListPop(&stackListNodeHead, &stackListNodeFreed);
    }
    clock_t end = clock();
    
    double timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\tВремя выполнения операций (реализация стека списком)  -  %lf\n", timeSpent);
    printf("\tКоличество памяти (реализация стека списком)  -  %lu\n", 1000 * sizeof(stackListNode_t));
    return timeSpent;
}



