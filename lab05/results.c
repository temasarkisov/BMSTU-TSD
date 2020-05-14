#include "results.h"

void makeZero(infoType *const info)
{
    info->currentLength = 0;
    info->lengthMid = 0;
    info->machineDowntime = 0;
    info->midTimeInQueue = 0;
    info->modellingTime = 0;
    info->totalInType1 = 0;
    info->totalInRequests = 0;
    info->totalInType2 = 0;
    info->totalOutType1 = 0;
    info->totalOutRequests = 0;
}

void showCommonResults(FILE *const stream, const infoType *const info, const int modelling_mode)
{
    if (modelling_mode == ARRAY)
    {
        fprintf(stream, "Итоговая статистика реализации статическим массивом:\n");
    }
    else
    {
        fprintf(stream, "Итоговая статистика реализации списком:\n");        
    }
    
    fprintf(stream, "%d - общее время моделирования(е.в)\n", (int) (info->modellingTime * 1000000));
    fprintf(stream, "%d - время простоя аппарата(е.в)\n", (int) (info->machineDowntime * 1000000));
    fprintf(stream, "%d - кол-во вошедших 1 типа\n", info->totalInType1);
    fprintf(stream, "%d - кол-во вышедших 1 типа\n", info->totalOutType1);
    fprintf(stream, "%d - кол-во обращений заявок 2 типа\n", info->totalInType2);
}

void showCurrentResults(FILE *const stream, const infoType *const info)
{
    fprintf(stream, "%d - текущая длина очереди\n", info->currentLength);
    fprintf(stream, "%f - средняя длина очереди\n", info->lengthMid);
    fprintf(stream, "%d - кол-во вошедших заявок\n", info->totalInRequests);
    fprintf(stream, "%d - кол-во вышедших заявок\n", info->totalOutRequests);
    fprintf(stream, "%f - среднее время пребывания заявки в очереди(е.в)\n\n", info->midTimeInQueue);
}