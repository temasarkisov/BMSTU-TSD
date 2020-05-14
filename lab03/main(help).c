#include "main.h"

int main()
{
    sparse_matrix_t sparse_matrix_a;
    matrix_t matrix_a;

    /*sparse_matrix_t sparse_matrix_b;
    sparse_matrix_t sparse_matrix_res;

    matrix_t matrix_b;
    matrix_t matrix_r;

    double time_sparse_matrix_sum;
    double time_matrix_sum;*/

    if (dime_input(&sparse_matrix_a.rows, &sparse_matrix_a.columns, &matrix_a.rows, &matrix_a.columns) == R_I)
    {

        sparse_matrix_allocate(&sparse_matrix_a);
        matrix_a = matrix_allocate(matrix_a);

        sparse_matrix_random_filling(&sparse_matrix_a, &matrix_a);
    }
}