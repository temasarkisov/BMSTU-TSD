#ifndef __SPARSE_MATRIX_OPER_H__
#define __SPARSE_MATRIX_OPER_H__

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"sparse_matrix_t.h"
#include"matrix_t.h"
#include"errno.h"

void column_sort_by_row_index(sparse_matrix_t *const sparse_matrix, const int start_index, const int end_index);

void sparse_matrix_sum(const sparse_matrix_t matrix1, const sparse_matrix_t matrix2, sparse_matrix_t *matrix);

double timer_for_sparse_matrix_sum(const sparse_matrix_t sparse_matrix_a, const sparse_matrix_t sparse_matrix_b, sparse_matrix_t *const sparse_matrix_r);

#endif
