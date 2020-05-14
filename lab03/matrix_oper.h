#ifndef __MATRIX_OPER_H__
#define __MATRIX_OPER_H__

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"sparse_matrix_t.h"
#include"matrix_t.h"
#include"errno.h"

void matrix_sum(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_r);

double timer_for_matrix_sum(const matrix_t matrix_a, const matrix_t matrix_b, matrix_t *const matrix_r);

#endif
