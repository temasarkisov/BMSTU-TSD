#include <stdio.h>
#include <stdlib.h>

double setTime(float downLimit, float upLimit)
{
    double k = (double) (rand() % 1000000) / 1000001;

    return ((upLimit - downLimit) * k + downLimit);
}

int main()
{
    double res = 1000000 * setTime((double) 0 / 1000000,(double) 5 / 1000000);
    printf("result = %f\n", res);
}
