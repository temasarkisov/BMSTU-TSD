#ifndef _RESULTS_H_
#define _RESULTS_H_

#include <stdio.h>
#include "main.h"
#include "structs.h"

void makeZero(infoType *const info);

void showCommonResults(FILE *const stream, const infoType *const info, const int modelling_mode);

void showCurrentResults(FILE *const stream, const infoType *const info);

#endif