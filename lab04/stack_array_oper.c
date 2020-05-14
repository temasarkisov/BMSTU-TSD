#include "stack_array_oper.h"

/* int stackArrayAllocate(stackArray_t *stackArray, const int stackMaxSize)
{
    stackArray->wordsArray = (char **) malloc(stackMaxSize * sizeof(char *));
    if (stackArray->wordsArray == NULL)
        return MEM_WAS_NOT_ALLOC; 

    return NO_ERR;
} */

int stackArrayPush(stackArray_t *stackArray, const int stackMaxSize, char *const wordNew)
{
    if (stackArray->stackSize == stackMaxSize)
        return STACK_OVERFLOW;

    (stackArray->stackSize)++;
    //stackArray->wordsArray = (char **) realloc(stackArray->wordsArray, stackArray->stackSize * sizeof(char *));
    
    /* if (stackArray->wordsArray == NULL)
        return MEM_WAS_NOT_ALLOC; */

    stackArray->wordsArray[stackArray->stackSize - 1] = wordNew;
    return NO_ERR; 
}

int stackArrayPop(stackArray_t *stackArray)
{
    if (stackArray->stackSize == 0)
        return STACK_UNDERFLOW;

    stackArray->stackSize--;
    //stackArray->wordsArray = (char **) realloc(stackArray->wordsArray, stackArray->stackSize * sizeof(char *));
    return NO_ERR;
}

void stackArrayPrint(stackArray_t const stackArray)
{
    for (int i = stackArray.stackSize - 1; i >= 0; i--)
    {
        if (i == 0)
            printf("%s\n", stackArray.wordsArray[i]);
        else
            printf("%s -> ", stackArray.wordsArray[i]);
    }
}

void stackArrayCondition(stackArray_t const stackArray, const int stackMaxSize)
{
    if (stackArray.stackSize == stackMaxSize)
        printf("\n\tСостояние стека: стек полностью заполнен (количество элементов в стеке  -  %d/%d)\n", stackArray.stackSize, stackMaxSize);

    else if (stackArray.stackSize == 0)
        printf("\n\tСостояние стека: стек пуст (количество элементов в стеке  -  %d)\n", stackArray.stackSize);

    else 
        printf("\n\tСостояние стека: количество элементов в стеке  -  %d/%d\n", stackArray.stackSize, stackMaxSize);
}