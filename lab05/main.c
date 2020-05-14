#include "main.h"

void showMenu()
{
    fprintf(stdout, "МЕНЮ:\n\
1  -  Провести моделирование(статичекий массив) и вывести результаты\n\
2  -  Провести моделирование(односвязный список) и вывести результаты\n\
3  -  Ввести время прибытия заявок и время обработки заявок\n\
4  -  Выйти из программы\n");
}

int showError(const int errCode)
{
    switch (errCode)
    {
        case WRONG_KEY:
            printf("Неверный код операции!\n");
            break;
        case QUEUE_REFILLED:
            printf("Очередь переполнена!\n");
            break;
        case QUEUE_IS_EMPTY:
            printf("Очередь пуста!\n");
            break;
        case WRONG_LIMITS:
            printf("Неправильный ввод временных параметров!\n");
            break;
    }

    return errCode;
}

void greeting()
{
    printf("Программа для моделирования очереди с использованием:\n\
а  -  Статического массива\n\
б  -  Односвязного списка\n\n");
}

void refreshData(queueArrayType *const attributes, int *const data)
{
    attributes->downLimit = data;
    attributes->upLimit = data + QUEUE_SIZE - 1;
    attributes->head = data + QUEUE_SIZE - 1;
    attributes->tail = data + QUEUE_SIZE - 1;
}

int main()
{
    bool process = true;
    int action = 0, maxSizeState = 0;
    srand(time(NULL));
    infoType results;
    rangeType range;
    makeZero(&results);
    clock_t operationsTiming = 0;

    // Статический массив
    int queue[QUEUE_SIZE];
    int timing[QUEUE_SIZE];
    queueArrayType attributes = { queue, queue + QUEUE_SIZE - 1, queue + QUEUE_SIZE - 1, queue + QUEUE_SIZE - 1};
    queueArrayType timingAttributes = { timing, timing + QUEUE_SIZE - 1, timing + QUEUE_SIZE - 1, timing + QUEUE_SIZE - 1};
    setDefault(&range);

    // Односвязный список
    queueType queueList = { NULL, 0 };

    greeting();
        
    while (process)
    {
        showMenu();

        if (fscanf(stdin, "%d", &action) != 1 || action < 1 || action > 4)
        {
            return showError(WRONG_KEY);
        }

        switch (action)
        {
            case MODELING_ARRAY:
                makeZero(&results);

                if (doModelingArray(&attributes, &timingAttributes, &range, &results, &maxSizeState, &operationsTiming) != OK)
                {
                    return showError(errno);
                }

                showCommonResults(stdout, &results, ARRAY);
                refreshData(&attributes, queue);
                refreshData(&timingAttributes, timing);
                printf("Затраты по памяти(байт) - %ld\n", maxSizeState * sizeof(int));
                printf("Общее время моделирования со статическим массивом - %f\n", (float) operationsTiming / CLOCKS_PER_SEC);
                maxSizeState = 0;
                operationsTiming = 0;
                break;
            case MODELING_LIST:
                makeZero(&results);

                if (doModelingList(&queueList, &range, &results, &maxSizeState, &operationsTiming) != OK)
                {
                    return showError(errno);
                }
                
                showCommonResults(stdout, &results, LIST);
                freeList(&queueList);
                queueList.size = 0;
                queueList.head = NULL;
                printf("Затраты по памяти(байт) - %ld\n", maxSizeState * (sizeof(struct listType) - sizeof(int)));
                printf("Общее время моделирования со списком - %f\n", (float) operationsTiming / CLOCKS_PER_SEC);
                maxSizeState = 0;
                operationsTiming = 0; 
                break;
            case SETUP_RANGE:
                if (inputRanges(stdin, stdout, &range) != OK)
                {
                    return showError(errno);
                }

                break;
            case EXIT:
                process = false;
                break;
        }
    }

    return OK;
}