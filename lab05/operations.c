#include "operations.h"

double setTime(float downLimit, float upLimit)
{
    double k = (double) (rand() % 1000000) / 1000001;

    return ((upLimit - downLimit) * k + downLimit);
}

void plusTiming(queueArrayType *const timing)
{
    for (int *p = timing->tail + 1; p <= timing->head; p++)
    {
        (*p)++;
    }
}

int doModelingArray(queueArrayType *const queue, queueArrayType *const timing, rangeType *const range,\
                      infoType *const info, int *const maxSizeState,  clock_t *const ticksTime)
{
    int recycledType1 = 0;
    int infoFlag = 0;
    int totalWaitingSum = 0;
    int timeArrival = 0;
    int timeCycling = 0;
    double timeSinceStart = 0.000000;
    double totalDowntime = 0.000000;
    int size = 0;
    clock_t startOperation = 0;
    clock_t endOperation = 0;

    int middleLengthSum = 0;
    int deleteCounter = 0;
    int inNumber = 0;
    int inType1 = 0;
    int outType1 = 0;
    int inType2 = 0;

    timeArrival = (int) round(1000000 * setTime((double) range->downArrival1 / 1000000, (double) range->upArrival1 / 1000000));

    startOperation = clock();
    addToTailArray(queue, TYPE_2);
    endOperation = clock();
    (*ticksTime) += endOperation - startOperation;
    addToTailArray(timing, 0);
    inNumber++;
    inType2++;

    while (recycledType1 < TOTAL_CYCLED)
    {
        size = queue->head - queue->tail;

        if (size > *maxSizeState)
        {
            *maxSizeState = size;
        }

        if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
        {
            infoFlag = recycledType1;
            info->currentLength = queue->head - queue->tail;
            info->lengthMid = middleLengthSum / (float) deleteCounter; 
            info->totalInRequests = inNumber;
            info->totalOutRequests = deleteCounter;
            info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
            fprintf(stdout, "Всего обработано заявок - %d\n", recycledType1);   
            showCurrentResults(stdout, info);
        }

        timeSinceStart += 0.000001;

        while (timeArrival == 0)
        {
            timeArrival = (int) round(1000000 * setTime((double) range->downArrival1 / 1000000, (double) range->upArrival1 / 1000000));
            startOperation = clock();

            if (addToTailArray(queue, TYPE_1) != OK)
            {
                return ERROR;
            }

            endOperation = clock();
            (*ticksTime) += endOperation - startOperation;

            if (addToTailArray(timing, 0) != OK)
            {
                return ERROR;
            }

            inNumber++;
            inType1++;
        }

        timeArrival -= 1;

        while (timeCycling == 0 && queue->head != queue->tail)
        {
            if (recycledType1 >= TOTAL_CYCLED)
            {
                break;
            }

            middleLengthSum += queue->head - queue->tail;
            deleteCounter++;

            if (*(queue->head) == TYPE_1)
            {
                timeCycling = (int) round(1000000 * setTime((double) range->downCycling1 / 1000000, (double) range->upCycling1 / 1000000));
                recycledType1++;
            }

            if (*(queue->head) == TYPE_2)
            {
                timeCycling = (int) round(1000000 * setTime((double) range->downCycling2 / 1000000, (double) range->upCycling2 / 1000000));
                inType2++;
                inNumber++;
            }
            else
            {
                outType1++;
            }

            // Код связанный с подсчетом среднего времени --------------------
            totalWaitingSum += *(timing->head);

            for (int *p = timing->head; p > timing->tail + 1; p--)
            {
                *(p) = *(p - 1);
            }

            (timing->tail)++;

            if (*(queue->head) == TYPE_2)
            {
                if (timing->head - (timing->tail + 1) < 4)
                {
                    addToTailArray(timing, 0);
                }
                else
                {
                    for (int *p = (timing->tail + 1) - 1; p < (timing->head) - 4; p++)
                    {
                        *(p) = *(p + 1);
                    }

                    *((timing->head) - 4) = 0;
                    (timing->tail)--;
                }
            }
            // ---------------------------------------------------------------
            startOperation = clock();

            if (removeFromHeadArray(queue) != OK)
            {
                return ERROR;
            }

            endOperation = clock();
            (*ticksTime) += endOperation - startOperation;

            if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
            {
                infoFlag = recycledType1;
                info->currentLength = queue->head - queue->tail;
                info->lengthMid = middleLengthSum / (float) deleteCounter; 
                info->totalInRequests = inNumber;
                info->totalOutRequests = deleteCounter;
                info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
                fprintf(stdout, "Всего обработано заявок 1 типа - %d\n", recycledType1);   
                showCurrentResults(stdout, info);
            }       
        }

        timeCycling -= 1;

        if (timeCycling < 0)
        {
            totalDowntime += 0.000001;
        }

        plusTiming(timing);
    }

    if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
    {
        infoFlag = recycledType1;
        info->currentLength = queue->head - queue->tail;
        info->lengthMid = middleLengthSum / (float) deleteCounter; 
        info->totalInRequests = inNumber;
        info->totalOutRequests = deleteCounter;
        info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
        fprintf(stdout, "Всего обработано заявок 1 типа - %d\n", recycledType1);   
        showCurrentResults(stdout, info);
    }

    info->modellingTime = timeSinceStart;
    info->machineDowntime = totalDowntime;
    info->totalInType1 = inType1;
    info->totalOutType1 = outType1;
    info->totalInType2 = inType2; 

    return OK;
}

int inputRanges(FILE *const inStream, FILE *const outStream, rangeType *const data)
{
    fprintf(outStream, "Введите нижнюю и верхнюю границу времени обработки заявок 1 типа(в е.в, натуральные числа либо 0):\n");
    
    if (fscanf(inStream, "%d %d", &(data->downCycling1), &(data->upCycling1)) != 2 || data->downCycling1 >= data->upCycling1 || data->downCycling1 < 0)
    {
        errno = WRONG_LIMITS;
        return ERROR;
    }

    fprintf(outStream, "Введите нижнюю и верхнюю границу времени прибытия заявок 1 типа(в е.в, натуральные числа либо 0):\n");

    if (fscanf(inStream, "%d %d", &(data->downArrival1), &(data->upArrival1)) != 2  || data->downArrival1 >= data->upArrival1 || data->downArrival1 < 0)
    {
        errno = WRONG_LIMITS;
        return ERROR;
    } 


    fprintf(outStream, "Введите нижнюю и верхнюю границу времени обработки заявок 2 типа(в е.в, натуральные числа либо 0):\n");
    
    if (fscanf(inStream, "%d %d", &(data->downCycling2), &(data->upCycling2)) != 2 || data->downCycling2 >= data->upCycling2 || data->downCycling2 < 0)
    {
        errno = WRONG_LIMITS;
        return ERROR;
    }

    return OK;
}

void setDefault(rangeType *const data)
{
    data->downArrival1 = DOWN_LIMIT_ARRIVAL_1;
    data->upArrival1 = UP_LIMIT_ARRIVAL_1;
    data->downCycling1 = DOWN_LIMIT_CYCLING_1;
    data->upCycling1 = UP_LIMIT_CYCLING_1;
    data->downCycling2 = DOWN_LIMIT_CYCLING_2;
    data->upCycling2 = UP_LIMIT_CYCLING_2;
}

void plusTimingList(queueType *const queue)
{
    listType *headCopy = queue->head;

    while (headCopy)
    {
        (headCopy->waitingTime)++;
        headCopy = headCopy->next;
    }
}

int doModelingList(queueType *const queue, rangeType *const range, infoType *const info, int *const maxSizeState, clock_t *const ticksTime)
{
    int recycledType1 = 0; 
    int infoFlag = 0;
    int  totalWaitingSum = 0;
    int timeArrival = 0;
    int  timeCycling = 0;
    double timeSinceStart = 0.000000;
    double totalDowntime = 0.000000;
    clock_t startOperation = 0;
    clock_t endOperation = 0;

    // Статистика
    int middleLengthSum = 0, deleteCounter = 0, inNumber = 0, inType1 = 0, outType1 = 0, inType2 = 0;

    timeArrival = (int) round(1000000 * setTime((double) range->downArrival1 / 1000000, (double) range->upArrival1 / 1000000));
    
    startOperation = clock();
    addToTailList(queue, TYPE_2, 0);
    endOperation = clock();
    (*ticksTime) += endOperation - startOperation;
    
    inNumber++;
    inType2++;

    while (recycledType1 < TOTAL_CYCLED)
    {
        if (queue->size > *maxSizeState)
        {
            *maxSizeState = queue->size;
        }

        if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
        {
            infoFlag = recycledType1;
            info->currentLength = queue->size;
            info->lengthMid = middleLengthSum / (float) deleteCounter; 
            info->totalInRequests = inNumber;
            info->totalOutRequests = deleteCounter;
            info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
            fprintf(stdout, "Всего обработано заявок - %d\n", recycledType1);   
            showCurrentResults(stdout, info);
        }

        timeSinceStart += 0.000001;

        while (timeArrival == 0)
        {
            timeArrival = (int) round(1000000 * setTime((double) range->downArrival1 / 1000000, (double) range->upArrival1 / 1000000));
           
            startOperation = clock();

            if (addToTailList(queue, TYPE_1, 0) != OK)
            {
                return ERROR;
            }

            endOperation = clock();
            (*ticksTime) += endOperation - startOperation;

            inNumber++;
            inType1++;
        }

        timeArrival -= 1;

        while (timeCycling == 0 && queue->size != 0)
        {
            if (recycledType1 >= TOTAL_CYCLED)
            {
                break;
            }

            middleLengthSum += queue->size;
            deleteCounter++;

            if (queue->head->type == TYPE_2)
            {
                timeCycling = (int) round(1000000 * setTime((double) range->downCycling2 / 1000000, (double) range->upCycling2 / 1000000));
                inType2++;
                inNumber++;
            }
            else
            {
                timeCycling = (int) round(1000000 * setTime((double) range->downCycling1 / 1000000, (double) range->upCycling1 / 1000000));
                outType1++;
                recycledType1++;
            }

            // Код связанный с подсчетом среднего времени --------------------

            totalWaitingSum += queue->head->waitingTime;

            startOperation = clock();

            if (removeFromHeadList(queue) != OK)
            {
                return ERROR;
            }

            endOperation = clock();
            (*ticksTime) += endOperation - startOperation;

            if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
            {
                infoFlag = recycledType1;
                info->currentLength = queue->size;
                info->lengthMid = middleLengthSum / (float) deleteCounter; 
                info->totalInRequests = inNumber;
                info->totalOutRequests = deleteCounter;
                info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
                fprintf(stdout, "Всего обработано заявок - %d\n", recycledType1);   
                showCurrentResults(stdout, info);
            }       
        }

        timeCycling -= 1;

        if (timeCycling < 0)
        {
            totalDowntime += 0.000001;
        }

        plusTimingList(queue);
    }

    if (recycledType1 % 100 == 0 && recycledType1 != 0 && recycledType1 != infoFlag)
    {
        infoFlag = recycledType1;
        info->currentLength = queue->size;
        info->lengthMid = middleLengthSum / (float) deleteCounter; 
        info->totalInRequests = inNumber;
        info->totalOutRequests = deleteCounter;
        info->midTimeInQueue = totalWaitingSum / (float) deleteCounter;
        fprintf(stdout, "Всего обработано заявок - %d\n", recycledType1);   
        showCurrentResults(stdout, info);
    }

    info->modellingTime = timeSinceStart;
    info->machineDowntime = totalDowntime;
    info->totalInType1 = inType1;
    info->totalOutType1 = outType1;
    info->totalInType2 = inType2;

    return OK;
}