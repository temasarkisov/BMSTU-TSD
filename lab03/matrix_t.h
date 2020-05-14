#ifndef __MATRIX_T_H__
#define __MATRIX_T_H__

//#define MATRIX_MAX_SIZE 1100

/*typedef struct {
    int matrix[MATRIX_MAX_SIZE][MATRIX_MAX_SIZE];
    int rows;
    int columns;
} matrix_t;*/

typedef struct {
    int **matrix;
    int rows;
    int columns;
} matrix_t;

#endif
